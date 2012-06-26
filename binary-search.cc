#include <stdio.h>
#include <assert.h>

#include "binary-search.hh"

/* Find paramater value within search_space s.t. func( param ) is close to goal */
real param_binary_search( Interval search_space,
			  std::function<real (const real)> func,
			  const real goal,
			  const bool slope )
{
  unsigned int iterations = 0;

  while ( 1 ) {
    real ret = search_space.middle();

    if ( search_space.width() < CONVERGENCE_GOAL ) {
      return ret;
    }

    const real val = func( ret );

    //    fprintf( stderr, "BINSRCH: try = %.10f, val = %.10f, goal = %.10f\n", ret, val, goal );

    if ( val > goal ) {
      (slope ? search_space.upper : search_space.lower) = ret;
    } else if ( val < goal ) {
      (slope ? search_space.lower : search_space.upper) = ret;
    } else {
      return ret;
    }

    iterations++;
    if ( iterations > ITERATION_LIMIT ) {
      fprintf( stderr, "Iteration limit %d exceeded.\n", ITERATION_LIMIT );
      throw;
    }
  }
}

real slow_search( Interval search_space,
		  std::function<real (const real)> func,
		  const real goal )
{
  real val = search_space.lower;
  double incr = (search_space.upper - search_space.lower) * .0000001;

  bool sign = (func( val ) > goal);

  fprintf( stderr, "Searching [%f, %f]\n", search_space.lower, search_space.upper );

  while ( val < search_space.upper - incr ) {
    val += incr;

    if ( (func( val ) > goal) != sign ) {
      fprintf( stderr, "Found inversion between %f (%f) and %f (%f)\n", val - incr, func( val - incr ), val, func( val ) );

      if ( sign ) {
	return val - incr;
      } else {
	return val;
      }
    }
  }

  fprintf( stderr, "REACHED END!\n" );
  return search_space.upper;
}
