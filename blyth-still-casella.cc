#include <algorithm>
#include <cassert>

#include "blyth-still-casella.hh"
#include "binary-search.hh"

void BlythStillCasella::verify_univariance( void ) const
{
  for ( unsigned int i = 0; i <= _N; i++ ) {
    assert( abs( upper_limits[ _N - i ] - (1 - lower_limits[ i ]) ) < 100 * CONVERGENCE_GOAL );
  }
}

void BlythStillCasella::refine_intervals( void ) {
  for ( unsigned int k = _N; k >= 1; k-- ) {
    auto binding_upper_limit_it = upper_bound( upper_limits.begin(),
					       upper_limits.end(),
					       lower_limits[ k ] );
    assert ( binding_upper_limit_it != upper_limits.end() );
    real binding_upper_limit = *binding_upper_limit_it;

    while ( 1 ) {
      real orig_value = lower_limits[ k ];
      param_binary_search( Interval( 0,
				     binding_upper_limit - orig_value ),
			   [&] (const real inc) -> real
			   {
			     lower_limits[ k ] = orig_value + inc;
			     upper_limits[ _N - k ] = 1 - lower_limits[ k ];
			     return this->coverage_probability( lower_limits[ k ] );
			   },
			   1 - _alpha,
			   false );
    assert( lower_limits[ k ] <= binding_upper_limit );

    if ( lower_limits[ k ] >= binding_upper_limit - 2 * CONVERGENCE_GOAL ) {
      lower_limits[ k ] = binding_upper_limit;
      upper_limits[ _N - k ] = 1 - lower_limits[ k ];
    }

    if ( (lower_limits[ k ] == binding_upper_limit)
	 && (coverage_probability( lower_limits[ k ] ) >= 1 - _alpha) ) {

	if ( binding_upper_limit_it + 1 == upper_limits.end() ) {
	  binding_upper_limit = 1.0;
	} else {
	  binding_upper_limit_it++;
	  binding_upper_limit = *binding_upper_limit_it;
	}
	continue;
      } else {
	break;
      }

      break;
    }

    assert ( this->coverage_probability( lower_limits[ k ] + 5 * CONVERGENCE_GOAL ) >= 1 - _alpha - 5 * CONVERGENCE_GOAL );
    assert ( this->coverage_probability( lower_limits[ k ] - 5 * CONVERGENCE_GOAL ) >= 1 - _alpha - 5 * CONVERGENCE_GOAL );
  }
}

BlythStillCasella::BlythStillCasella( const IntervalCollection & unrefined_interval )
  : _N( unrefined_interval.N() ),
    _alpha( unrefined_interval.alpha() ),
    lower_limits( _N + 1 ),
    upper_limits( _N + 1 )
{
  /* collect underlying intervals */
  for ( unsigned int i = 0; i <= _N; i++ ) {
    const Interval x( unrefined_interval.limits[ i ] );

    lower_limits[ i ] = x.lower;
    upper_limits[ i ] = x.upper;
  }

  verify_univariance();
  refine_intervals();
  verify_univariance();
}

real BlythStillCasella::coverage_probability( const real p ) const
{
  real sum = 0;
  for ( unsigned int x = 0; x <= _N; x++ ) {
    if ( (lower_limits[ x ] < p) && (p < upper_limits[ x ]) ) {
      sum += exp( likeln( _N, x, p ) );
    }
  }
  return sum;
}

const IntervalCollection BlythStillCasella::limits( void ) const
{
  IntervalCollection ret( _N, _alpha );
  for ( unsigned int i = 0; i <= _N; i++ ) {
    ret.limits[ i ] = limits( i );
  }
  return ret;
}
