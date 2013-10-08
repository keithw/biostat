#ifndef UTIL_HH
#define UTIL_HH

#include <vector>

typedef double real;

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

/* cached version */
class LikelnCache
{
private:
  const unsigned int _p_slots;
  std::vector< std::vector< real > > _cache;

public:
  LikelnCache( const unsigned int N, const unsigned int s_slots );

  real likeln( const int i, const real p ) const { return _cache.at( i ).at( p * _p_slots ); }
};

#endif
