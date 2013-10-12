#ifndef BARNARDBB_HH
#define BARNARDBB_HH

#include <vector>

#include "util.hh"

class Barnard
{
protected:
  const unsigned int M_, N_;

private:
  const breal gamma_;

  virtual breal particular_p_value( const unsigned int count, const breal pi ) const;

  const IntervalCollection M_search, N_search;

  class PossibleOutcome {
  private:
    breal bicoln_cache;

  public:
    unsigned int i, j;
    unsigned int M, N;
    breal d;

    PossibleOutcome( const unsigned int s_i,
		     const unsigned int s_j,
		     const unsigned int s_M,
		     const unsigned int s_N );

    /* probability of this outcome if pi1 = pi2 = p */
    breal likeln( const breal p ) const;

    bool operator<( const PossibleOutcome & other ) const { return d > other.d; }
  };

protected:
  std::vector< PossibleOutcome > outcomes;

public:
  Barnard( const unsigned int s_M,
	   const unsigned int s_N,
	   const breal s_gamma );

  virtual breal p_value( const unsigned int i, const unsigned int j, const breal p_step ) const;

  virtual ~Barnard() {}
};

class BarnardFast : public Barnard
{
private:
  const unsigned int p_slots_;
  std::vector< std::vector< bool > > ppv_cache_;

public:
  BarnardFast( const unsigned int s_M,
	       const unsigned int s_N,
	       const breal s_gamma,
	       const breal s_slots,
	       const breal alpha );

  breal particular_p_value( const unsigned int count, const breal pi ) const
  {
    return ppv_cache_.at( count ).at( pi * p_slots_ );
  }

  breal p_value( const unsigned int i, const unsigned int j ) const
  {
    return Barnard::p_value( i, j, 1.0 / p_slots_ );
  }
};

#endif
