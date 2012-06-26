#include <stdio.h>
#include <algorithm>
#include <assert.h>

#include "coverage-graph.hh"

template <class IntervalProcedure>
CoverageGraph<IntervalProcedure>::CoverageGraph( const unsigned int s_N, const real s_alpha )
  : _N( s_N ),
    _alpha( s_alpha ),
    limits( _N + 1, Interval( 0, 1 ) )
{
  /* collect underlying intervals */
  IntervalProcedure interval( _N, _alpha );

  for ( unsigned int i = 0; i <= _N; i++ ) {
    limits[ i ] = interval.limits( i );
  }
}

template <class IntervalProcedure>
real CoverageGraph<IntervalProcedure>::coverage_probability( const real p ) const
{
  real sum = 0;
  for ( unsigned int x = 0; x <= _N; x++ ) {
    if ( (limits[ x ].lower <= p) && (p <= limits[ x ].upper) ) { /* closed when evaluating */
      sum += exp( likeln( _N, x, p ) );
    }
  }
  return sum;
}
