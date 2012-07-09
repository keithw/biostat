#ifndef BLYTH_STILL_CASELLA_HH
#define BLYTH_STILL_CASELLA_HH

#include <vector>

#include "util.hh"

class BlythStillCasella
{
 private:
  const unsigned int _N;
  const real _alpha;

  std::vector< real > lower_limits, upper_limits;

  real coverage_probability( const real p ) const;

  void verify_univariance( void ) const;
  void refine_intervals( void );

 public:
  BlythStillCasella( const IntervalCollection & unrefined_interval );

  Interval limits( const unsigned int k ) const { return Interval( lower_limits[ k ],
								   upper_limits[ k ] ); }

  const IntervalCollection limits( void ) const;
};

#endif
