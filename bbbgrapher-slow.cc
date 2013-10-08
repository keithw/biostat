#include <cmath>
#include <iostream>
#include <array>

#include "barnardbb.hh"

const unsigned int N = 700, M = 500;
const real alpha = 0.05;
const unsigned int p_quantizer_steps = 1000;
const real berger_boos_gamma = 1e-06;

using namespace std;

int main( void )
{
  cerr << "Calculating Barnard (Berger-Boos) test for " << N << "x" << M << " outcomes... ";

  BarnardFast bbb( N, M, berger_boos_gamma, p_quantizer_steps );
  array< array< bool, M + 1 >, N + 1 > test_result;

  for ( unsigned int i = 0; i <= N; i++ ) {
    for ( unsigned int j = 0; j <= M; j++ ) {
      test_result.at( i ).at( j ) = ( bbb.p_value( i, j ) < alpha );
    }
  }

  cerr << "done." << endl << "Calculating binomial coefficient caches... ";

  LikeCache icache( N, p_quantizer_steps ), jcache( M, p_quantizer_steps );

  cerr << "done." << endl << "Printing curve of false positive probabilities... ";

  for ( unsigned int pint = 1; pint < p_quantizer_steps; pint++ ) {
    const real p = real( pint ) / real( p_quantizer_steps );
    real false_positive_probability = 0.0;

    for ( unsigned int i = 0; i <= N; i++ ) {
      const real prob_of_i = icache.like( i, p );
      for ( unsigned int j = 0; j <= M; j++ ) {
	if ( test_result.at( i ).at( j ) ) {
	  const real prob_of_j = jcache.like( j, p );
	  false_positive_probability += prob_of_i * prob_of_j;
	}
      }
    }

    cout << p << " " << false_positive_probability << endl;
  }

  cerr << "done." << endl;

  return EXIT_SUCCESS;
}