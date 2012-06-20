#ifndef UTIL_HH
#define UTIL_HH

#include <math.h>

typedef long double real;

class Interval
{
public:
  real lower;
  real upper;

  Interval( const real s_lower, const real s_upper );

  real middle( void ) const;
  real width( void ) const;
};

/* log factorial */
real factln( const int N );

/* log binomial coefficient (N choose k) */
real bicoln( const int N, const int k );

/* log prob that N draws from a binomial RV with prob p gives k successes */
real likeln( const int N, const int k, const real p );

#endif
