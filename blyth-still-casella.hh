#ifndef BLYTH_STILL_CASELLA_HH
#define BLYTH_STILL_CASELLA_HH

#include <vector>

#include "util.hh"

template <class UnrefinedProcedure>
class BlythStillCasella
{
 private:
  const unsigned int _N;
  const real _alpha;

  std::vector< real > lower_limits, upper_limits;

  real coverage_probability( const real p ) const;

 public:
  BlythStillCasella( const unsigned int s_N, const real s_alpha );

  Interval limits( const unsigned int k ) const { return Interval( lower_limits[ k ],
								   upper_limits[ k ] ); }
};

#endif
