#include "clopper-pearson.hh"
#include "binary-search.hh"

ClopperPearson::ClopperPearson( const int s_N, const real s_alpha )
  : _N( s_N ),
    _alpha( s_alpha )
{
}

static real sum_integer_binomial_range( const unsigned int N,
					const unsigned int lower, const unsigned int upper,
					const real p )
{
  real sum( 0 );

  for ( unsigned int i = lower; i <= upper; i++ ) {
    sum += expl( likeln( N, i, p ) );
  }

  return sum;
}

Interval ClopperPearson::limits( const int k )
{
  Interval ret( 0, 1 );

  real estimate = real(k) / real(_N);

  /* calculate lower limit */
  if ( k != 0 ) {
    ret.lower = param_binary_search( Interval( 0, estimate ),
				     [&] (const real p)
				     {
				       return sum_integer_binomial_range( _N, k, _N, p );
				     },
				     _alpha / 2.0,
				     true );
  }

  /* calculate upper limit */
  if ( k != _N ) {
    ret.upper = param_binary_search( Interval( estimate, 1 ),
				     [&] (const real p)
				     {
				       return sum_integer_binomial_range( _N, 0, k, p );
				     },
				     _alpha / 2.0,
				     false );
  }

  return ret;
}
