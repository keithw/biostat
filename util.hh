#ifndef UTIL_HH
#define UTIL_HH

#include <math.h>

typedef double real;

#define realgamma tgamma
#define realgammaln lgamma
#define reallog log
#define realexp exp
#define realpow pow
#define realabs fabs

class Interval
{
public:
  real lower;
  real upper;

  Interval( const real s_lower, const real s_upper );

  real middle( void ) const;
  real width( void ) const;
};

/* factorial */
real factln( const unsigned int N );

/* binomial coefficient (N choose k) */
real bicoln( const unsigned int N, const unsigned int k );

/* prob that N draws from a binomial RV with prob p gives k successes */
real likeln( const unsigned int N, const unsigned int k, const real p );

#endif
