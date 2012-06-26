#ifndef COVERAGE_GRAPH_HH
#define COVERAGE_GRAPH_HH

#include <vector>

#include "util.hh"

template <class IntervalProcedure>
class CoverageGraph
{
 private:
  const unsigned int _N;
  const real _alpha;

  std::vector< Interval > limits;

 public:
  CoverageGraph( const unsigned int s_N, const real s_alpha );

  real coverage_probability( const real p ) const;
};

#endif
