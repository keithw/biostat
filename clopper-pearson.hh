#ifndef CLOPPER_PEARSON_HH
#define CLOPPER_PEARSON_HH

#include "util.hh"

class ClopperPearson
{
private:
  IntervalCollection _limits;

public:
  /* N draws, with confidence parameter alpha */
  ClopperPearson( const unsigned int s_N, const real s_alpha );

  /* Confidence interval when N draws give k successes */
  const IntervalCollection & limits( void ) const { return _limits; }
};

#endif
