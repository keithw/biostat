#include <cmath>

#include "coverage-graph.hh"

breal CoverageGraph::coverage_probability( const breal p, const IntervalCollection & limits )
{
  breal sum = 0;
  for ( unsigned int x = 0; x <= limits.N(); x++ ) {
    if ( (limits.limits[ x ].lower <= p) && (p <= limits.limits[ x ].upper) ) { /* closed when evaluating */
      sum += std::exp( likeln( limits.N(), x, p ) );
    }
  }
  return sum;
}
