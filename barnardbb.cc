#include <algorithm>
#include <iostream>

#include "barnardbb.hh"
#include "clopper-pearson.hh"
#include "blyth-still-casella.hh"

Barnard::PossibleOutcome::PossibleOutcome( const unsigned int s_i,
					   const unsigned int s_j,
					   const unsigned int s_M,
					   const unsigned int s_N )
  : bicoln_cache( bicoln( s_M, s_i ) + bicoln( s_N, s_j ) ),
    i( s_i ), j( s_j ),
    M( s_M ), N( s_N ),
    d( 0.0 )
{
  if ( i == 0 && j == 0 ) {
    return;
  }

  if ( i == M && j == N ) {
    return;
  }

  real pi1hat = real( i ) / real( M );
  real pi2hat = real( j ) / real( N );

  real denom1 = real( i + j ) / real( M + N );
  real denom2 = real( (M - i) + (N - j) ) / real( M + N );
  real denom3 = 1.0 / real( M ) + 1.0 / real( N );

  real numer = pi2hat - pi1hat;
  real denom = std::sqrt( denom1 * denom2 * denom3 );

  d = std::abs( numer / denom );
}

real Barnard::PossibleOutcome::likeln( const real p ) const
{
  return bicoln_cache + (i + j) * std::log( p ) + ( (M - i) + (N - j) ) * std::log( 1 - p );
}

Barnard::Barnard( const unsigned int s_M,
		  const unsigned int s_N,
		  const real s_gamma )
  : _M( s_M ), _N( s_N ),
    _gamma( s_gamma ),
    M_search( BlythStillCasella( ClopperPearson( s_M, _gamma / 2.0 ).limits() ).limits() ),
    N_search( BlythStillCasella( ClopperPearson( s_N, _gamma / 2.0 ).limits() ).limits() ),
    outcomes()
{
  for ( unsigned int i = 0; i <= _M; i++ ) {
    for ( unsigned int j = 0; j <= _N; j++ ) {
      outcomes.push_back( PossibleOutcome( i, j, _M, _N ) );
    }
  }

  sort( outcomes.begin(), outcomes.end() );
}

real Barnard::p_value( const unsigned int i, const unsigned int j, const real p_step ) const
{
  if ( i == 0 && j == 0 ) {
    return 1.0;
  }

  if ( i == _M && j == _N ) {
    return 1.0;
  }

  /* count more extreme possible outcomes */
  auto set = upper_bound( outcomes.begin(), outcomes.end(),
			  PossibleOutcome( i, j, _M, _N ) );
  unsigned int count = set - outcomes.begin();

  /* find search limits using Berger-Boos procedure */
  const Interval & limits1 = M_search.limits[ i ];
  const Interval & limits2 = N_search.limits[ j ];

  Interval search( std::max( 0.0, std::max( limits1.lower, limits2.lower ) - p_step ),
		   std::min( 1.0, std::min( limits1.upper, limits2.upper ) + p_step ) );

  real ret = 0;
  for ( real p = search.lower; p <= search.upper; p += p_step ) {
    ret = std::max( ret, particular_p_value( count, p ) );
  }

  return std::min( 1.0, ret + _gamma );
}

real Barnard::particular_p_value( const unsigned int count, const real pi ) const
{
  real ret = 0;

  for ( unsigned int x = 0; x < count; x++ ) {
    ret += std::exp( outcomes[ x ].likeln( pi ) );
  }

  return ret;
}

BarnardFast::BarnardFast( const unsigned int s_M,
			  const unsigned int s_N,
			  const real s_gamma,
			  const real s_slots )
  : Barnard( s_M, s_N, s_gamma ),
    _p_slots( s_slots ),
    _ppv_cache( (_M + 1) * (_N + 1) + 1, std::vector< float >( _p_slots + 1, -1 ) )
{
  /* make the cache in fast order */
  for ( unsigned int pslot = 0; pslot <= _p_slots; pslot++ ) {
    real cumulative_probability = 0.0;
    _ppv_cache.at( 0 ).at( pslot ) = cumulative_probability;
    for ( unsigned int count = 1; count <= outcomes.size(); count++ ) {
      cumulative_probability += std::exp( outcomes.at( count - 1 ).likeln( real( pslot ) / real( _p_slots ) ) );
      _ppv_cache.at( count ).at( pslot ) = cumulative_probability;
    }
  }
}
