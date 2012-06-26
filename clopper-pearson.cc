#include <stdio.h>
#include <boost/math/special_functions/beta.hpp>

#include "clopper-pearson.hh"
#include "binary-search.hh"

ClopperPearson::ClopperPearson( const unsigned int s_N, const real s_alpha )
  : _N( s_N ),
    _alpha( s_alpha )
{
}

Interval ClopperPearson::limits( const unsigned int k )
{
  Interval ret( 0, 1 );

  /* calculate lower limit */
  if ( k != 0 ) {
    ret.lower = boost::math::ibeta_inv( k, _N - k + 1, _alpha / 2.0 );
  }

  /* calculate upper limit */
  if ( k != _N ) {
    ret.upper = boost::math::ibeta_inv( k + 1, _N - k, 1 - _alpha / 2.0 );
  }

  return ret;
}
