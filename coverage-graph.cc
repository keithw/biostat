#include "coverage-graph.hh"

real CoverageGraph::coverage_probability( const real p, const IntervalCollection & limits )
{
  real sum = 0;
  for ( unsigned int x = 0; x <= limits.N(); x++ ) {
    if ( (limits.limits[ x ].lower <= p) && (p <= limits.limits[ x ].upper) ) { /* closed when evaluating */
      sum += exp( likeln( limits.N(), x, p ) );
    }
  }
  return sum;
}
