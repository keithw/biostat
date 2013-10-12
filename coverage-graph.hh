#ifndef COVERAGE_GRAPH_HH
#define COVERAGE_GRAPH_HH

#include <vector>

#include "util.hh"

class CoverageGraph
{
 public:
  static breal coverage_probability( const breal p, const IntervalCollection & limits );
};

#endif
