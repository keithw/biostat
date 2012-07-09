#ifndef UTIL_HH
#define UTIL_HH

#include <math.h>
#include <vector>

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

class IntervalCollection
{
private:
  const unsigned int _N;
  const real _alpha;

public:
  std::vector<Interval> limits;

  IntervalCollection( const unsigned int s_N, const real s_alpha )
    : _N( s_N ),
      _alpha( s_alpha ),
      limits( _N + 1, Interval( 0, 1 ) )
  {}

  unsigned int N( void ) const { return _N; }
  real alpha( void ) const { return _alpha; }
};

/* factorial */
real factln( const unsigned int N );

/* binomial coefficient (N choose k) */
real bicoln( const unsigned int N, const unsigned int k );

/* prob that N draws from a binomial RV with prob p gives k successes */
real likeln( const unsigned int N, const unsigned int k, const real p );

#endif
