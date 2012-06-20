#ifndef CLOPPER_PEARSON_HH
#define CLOPPER_PEARSON_HH

#include "util.hh"

class ClopperPearson
{
private:
  const int _N;
  const real _alpha;

public:
  /* N draws, with confidence parameter alpha */
  ClopperPearson( const int s_N, const real s_alpha );

  /* Confidence interval when N draws give k successes */
  Interval limits( const int k );
};

#endif
