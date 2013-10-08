#include <boost/math/special_functions/gamma.hpp>
#include <vector>

#include "util.hh"

Interval::Interval( const real s_lower, const real s_upper )
  : lower( s_lower ),
    upper( s_upper )
{
}

real Interval::middle( void ) const
{
  return (lower + upper) / 2.0;
}

real Interval::width( void ) const
{
  return upper - lower;
}

/* log factorial */
real factln( const unsigned int N )
{
  return boost::math::lgamma( real(N) + 1.0 );
}

/* log binomial coefficient (N choose k) */
real bicoln_raw( const unsigned int N, const unsigned int k )
{
  return factln( N ) - factln( k ) - factln( N - k );
}

/* log prob that N draws from a binomial RV with prob p gives k successes */
real likeln( const unsigned int N, const unsigned int k, const real p ) {
  return bicoln( N, k ) + k * log( p ) + (N - k) * log( 1 - p );
}

/* memoized version */
real bicoln( const unsigned int N, const unsigned int k )
{
  static std::vector< std::vector< real > > cache;

  if ( N >= cache.size() ) {
    unsigned int old_size = cache.size();

    cache.resize( N + 1 );

    for ( unsigned int candidate_N = old_size; candidate_N < cache.size(); candidate_N++ ) {
      cache.at( candidate_N ).resize( candidate_N + 1 );
      for ( unsigned int candidate_k = 0; candidate_k <= candidate_N; candidate_k++ ) {
	cache.at( candidate_N ).at( candidate_k ) = bicoln_raw( candidate_N, candidate_k );
      }
    }
  }

  return cache.at( N ).at( k );
}
