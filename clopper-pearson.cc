#include <stdio.h>
#include <boost/math/special_functions/beta.hpp>

#include "clopper-pearson.hh"
#include "binary-search.hh"

ClopperPearson::ClopperPearson( const unsigned int s_N, const real s_alpha )
  : _limits( s_N, s_alpha )
{
  for ( unsigned int k = 0; k <= s_N; k++ ) {
    /* calculate lower limit */
    if ( k != 0 ) {
      _limits.limits[ k ].lower = boost::math::ibeta_inv( k, s_N - k + 1, s_alpha / 2.0 );
    }

    /* calculate upper limit */
    if ( k != s_N ) {
      _limits.limits[ k ].upper = boost::math::ibeta_inv( k + 1, s_N - k, 1 - s_alpha / 2.0 );
    }
  }
}
