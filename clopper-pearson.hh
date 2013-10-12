#ifndef CLOPPER_PEARSON_HH
#define CLOPPER_PEARSON_HH

#include "util.hh"

class ClopperPearson
{
private:
  IntervalCollection limits_;

public:
  /* N draws, with confidence parameter alpha */
  ClopperPearson( const unsigned int s_N, const breal s_alpha );

  /* Confidence interval when N draws give k successes */
  const IntervalCollection & limits( void ) const { return limits_; }
};

#endif
