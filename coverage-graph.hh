#ifndef COVERAGE_GRAPH_HH
#define COVERAGE_GRAPH_HH

#include <vector>

#include "util.hh"

class CoverageGraph
{
 public:
  static real coverage_probability( const real p, const IntervalCollection & limits );
};

#endif
