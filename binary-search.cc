#include <iostream>

#include "binary-search.hh"

using namespace std;

/* Find paramater value within search_space s.t. func( param ) is close to goal */
breal param_binary_search( Interval search_space,
			  function<breal (const breal)> func,
			  const breal goal,
			  const bool slope )
{
  unsigned int iterations = 0;

  while ( 1 ) {
    breal ret = search_space.middle();

    if ( search_space.width() < CONVERGENCE_GOAL ) {
      return ret;
    }

    const breal val = func( ret );

    if ( val > goal ) {
      (slope ? search_space.upper : search_space.lower) = ret;
    } else if ( val < goal ) {
      (slope ? search_space.lower : search_space.upper) = ret;
    } else {
      return ret;
    }

    iterations++;
    if ( iterations > ITERATION_LIMIT ) {
      cerr << "Iteration limit exceeded." << endl;
      throw;
    }
  }
}
