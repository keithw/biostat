#include <algorithm>
#include <iostream>

#include "barnardbb.hh"
#include "clopper-pearson.hh"
#include "blyth-still-casella.hh"

using namespace std;

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

  breal pi1hat = breal( i ) / breal( M );
  breal pi2hat = breal( j ) / breal( N );

  breal denom1 = breal( i + j ) / breal( M + N );
  breal denom2 = breal( (M - i) + (N - j) ) / breal( M + N );
  breal denom3 = 1.0 / breal( M ) + 1.0 / breal( N );

  breal numer = pi2hat - pi1hat;
  breal denom = sqrt( denom1 * denom2 * denom3 );

  d = abs( numer / denom );
}

breal Barnard::PossibleOutcome::likeln( const breal p ) const
{
  return bicoln_cache + (i + j) * log( p ) + ( (M - i) + (N - j) ) * log( 1 - p );
}

Barnard::Barnard( const unsigned int s_M,
		  const unsigned int s_N,
		  const breal s_gamma )
  : M_( s_M ), N_( s_N ),
    gamma_( s_gamma ),
    M_search( BlythStillCasella( ClopperPearson( s_M, gamma_ / 2.0 ).limits() ).limits() ),
    N_search( BlythStillCasella( ClopperPearson( s_N, gamma_ / 2.0 ).limits() ).limits() ),
    outcomes()
{
  for ( unsigned int i = 0; i <= M_; i++ ) {
    for ( unsigned int j = 0; j <= N_; j++ ) {
      outcomes.push_back( PossibleOutcome( i, j, M_, N_ ) );
    }
  }

  sort( outcomes.begin(), outcomes.end() );
}

breal Barnard::p_value( const unsigned int i, const unsigned int j, const breal p_step ) const
{
  if ( i == 0 && j == 0 ) {
    return 1.0;
  }

  if ( i == M_ && j == N_ ) {
    return 1.0;
  }

  /* count more extreme possible outcomes */
  auto set = upper_bound( outcomes.begin(), outcomes.end(),
			  PossibleOutcome( i, j, M_, N_ ) );
  unsigned int count = set - outcomes.begin();

  /* find search limits using Berger-Boos procedure */
  const Interval & limits1 = M_search.limits[ i ];
  const Interval & limits2 = N_search.limits[ j ];

  Interval search( max( 0.0, max( limits1.lower, limits2.lower ) - p_step ),
		   min( 1.0, min( limits1.upper, limits2.upper ) + p_step ) );

  breal ret = 0;
  for ( breal p = search.lower; p <= search.upper; p += p_step ) {
    ret = max( ret, particular_p_value( count, p ) );
  }

  return min( 1.0, ret + gamma_ );
}

breal Barnard::particular_p_value( const unsigned int count, const breal pi ) const
{
  breal ret = 0;

  for ( unsigned int x = 0; x < count; x++ ) {
    ret += exp( outcomes[ x ].likeln( pi ) );
  }

  return ret;
}

BarnardFast::BarnardFast( const unsigned int s_M,
			  const unsigned int s_N,
			  const breal s_gamma,
			  const breal s_slots,
			  const breal alpha )
  : Barnard( s_M, s_N, s_gamma ),
    p_slots_( s_slots ),
    ppv_cache_( (M_ + 1) * (N_ + 1) + 1, vector< bool >( p_slots_ + 1, -1 ) )
{
  /* make the cache in fast order */
  for ( unsigned int pslot = 0; pslot <= p_slots_; pslot++ ) {
    breal cumulative_probability = 0.0;
    ppv_cache_.at( 0 ).at( pslot ) = cumulative_probability;
    for ( unsigned int count = 1; count <= outcomes.size(); count++ ) {
      cumulative_probability += exp( outcomes.at( count - 1 ).likeln( breal( pslot ) / breal( p_slots_ ) ) );
      ppv_cache_.at( count ).at( pslot ) = cumulative_probability >= alpha;
    }
  }
}
