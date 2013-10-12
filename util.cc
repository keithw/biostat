#include <boost/math/special_functions/gamma.hpp>
#include <vector>

#include "util.hh"

using namespace std;

Interval::Interval( const breal s_lower, const breal s_upper )
  : lower( s_lower ),
    upper( s_upper )
{
}

breal Interval::middle( void ) const
{
  return (lower + upper) / 2.0;
}

breal Interval::width( void ) const
{
  return upper - lower;
}

/* log factorial */
breal factln( const unsigned int N )
{
  return boost::math::lgamma( breal(N) + 1.0 );
}

/* log binomial coefficient (N choose k) */
breal bicoln_raw( const unsigned int N, const unsigned int k )
{
  return factln( N ) - factln( k ) - factln( N - k );
}

/* log prob that N draws from a binomial RV with prob p gives k successes */
breal likeln( const unsigned int N, const unsigned int k, const breal p ) {
  return bicoln( N, k ) + k * log( p ) + (N - k) * log( 1 - p );
}

/* memoized version */
breal bicoln( const unsigned int N, const unsigned int k )
{
  static vector< vector< breal > > cache;

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

long int myatoi( const string & str )
{
  char *end;

  errno = 0;
  long int ret = strtol( str.c_str(), &end, 10 );

  if ( ( errno != 0 )
       || ( end != str.c_str() + strlen( str.c_str() ) ) ) {
    cerr << "Bad integer: " << str << endl;
    throw;
  }

  return ret;
}

double myatof( const string & str )
{
  char *end;

  errno = 0;
  double ret = strtod( str.c_str(), &end );

  if ( ( errno != 0 )
       || ( end != str.c_str() + strlen( str.c_str() ) ) ) {
    cerr << "Bad floating-point number: " << str << endl;
    throw;
  }

  return ret;
}
