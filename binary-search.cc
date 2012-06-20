#include "binary-search.hh"

/* Find paramater value within search_space s.t. func( param ) is close to goal */
real param_binary_search( Interval search_space,
			  std::function<real (const real)> func,
			  const real goal,
			  const bool slope )
{
  while ( 1 ) {
    real ret = search_space.middle();

    if ( search_space.width() < CONVERGENCE_GOAL ) {
      return ret;
    }

    const real val = func( ret );

    if ( val > goal ) {
      (slope ? search_space.upper : search_space.lower) = ret;
    } else if ( val < goal ) {
      (slope ? search_space.lower : search_space.upper) = ret;
    } else {
      return ret;
    }
  }
}
