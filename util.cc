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
real factln( const int N )
{
  return lgammal( real(N) + 1.0 );
}

/* log binomial coefficient (N choose k) */
real bicoln( const int N, const int k )
{
  return factln( N ) - factln( k ) - factln( N - k );
}

/* log prob that N draws from a binomial RV with prob p gives k successes */
real likeln( const int N, const int k, const real p ) {
  return bicoln( N, k ) + k * logl( p ) + (N - k) * logl( 1 - p );
}
