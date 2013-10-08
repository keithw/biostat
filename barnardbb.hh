#ifndef BARNARDBB_HH
#define BARNARDBB_HH

#include <vector>

#include "util.hh"

class Barnard
{
protected:
  const unsigned int _M, _N;

private:
  const real _gamma;

  virtual real particular_p_value( const unsigned int count, const real pi ) const;

  const IntervalCollection M_search, N_search;

  class PossibleOutcome {
  private:
    real bicoln_cache;

  public:
    unsigned int i, j;
    unsigned int M, N;
    real d;

    PossibleOutcome( const unsigned int s_i,
		     const unsigned int s_j,
		     const unsigned int s_M,
		     const unsigned int s_N );

    /* probability of this outcome if pi1 = pi2 = p */
    real likeln( const real p ) const;

    bool operator<( const PossibleOutcome &other ) const { return d > other.d; }
  };

protected:
  std::vector< PossibleOutcome > outcomes;

public:
  Barnard( const unsigned int s_M,
	   const unsigned int s_N,
	   const real s_gamma );

  real p_value( const unsigned int i, const unsigned int j ) const;

  virtual ~Barnard() {}
};

class BarnardFast : public Barnard
{
private:
  const unsigned int _p_slots;
  std::vector< std::vector< float > > _ppv_cache;

public:
  BarnardFast( const unsigned int s_M,
	       const unsigned int s_N,
	       const real s_gamma,
	       const real s_slots );

  real particular_p_value( const unsigned int count, const real pi ) const
  {
    return _ppv_cache[ count ][ pi * _p_slots ];
  }
};

#endif
