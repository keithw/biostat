#ifndef BINARY_SEARCH_HH
#define BINARY_SEARCH_HH

#include <functional>

#include "util.hh"

const real CONVERGENCE_GOAL = 1e-13;
const unsigned int ITERATION_LIMIT = 100;

/* Find paramater value within search_space s.t. func( param ) is close to goal */
real param_binary_search( Interval search_space,
			  std::function<real (const real)> func,
			  const real goal,
			  const bool slope );

#endif
