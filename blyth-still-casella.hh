#ifndef BLYTH_STILL_CASELLA_HH
#define BLYTH_STILL_CASELLA_HH

#include <vector>

#include "util.hh"

class BlythStillCasella
{
 private:
  const unsigned int N_;
  const breal alpha_;

  std::vector< breal > lower_limits, upper_limits;

  breal coverage_probability( const breal p ) const;

  void verify_univariance( void ) const;
  void refine_intervals( void );

 public:
  BlythStillCasella( const IntervalCollection & unrefined_interval );

  Interval limits( const unsigned int k ) const { return Interval( lower_limits[ k ],
								   upper_limits[ k ] ); }

  const IntervalCollection limits( void ) const;
};

#endif
