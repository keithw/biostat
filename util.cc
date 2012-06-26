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
  return realgammaln( real(N) + 1.0 );
}

/* log binomial coefficient (N choose k) */
real bicoln( const unsigned int N, const unsigned int k )
{
  return factln( N ) - factln( k ) - factln( N - k );
}

/* log prob that N draws from a binomial RV with prob p gives k successes */
real likeln( const unsigned int N, const unsigned int k, const real p ) {
  return bicoln( N, k ) + k * reallog( p ) + (N - k) * reallog( 1 - p );
}
