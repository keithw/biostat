#include <cmath>
#include <iostream>
#include <array>

#include "barnardbb.hh"

const breal alpha = 0.05;
const unsigned int p_quantizer_steps = 1000;
const breal berger_boos_gamma = 1e-06;

using namespace std;

int main( int argc, char *argv[] )
{
  if ( argc < 3 ) {
    cerr << "Usage: " << argv[ 0 ] << " N M" << endl;
    return EXIT_FAILURE;
  }

  const unsigned int N = myatoi( argv[ 1 ] ), M = myatoi( argv[ 2 ] );

  cerr << "Calculating Barnard (Berger-Boos) test for " << N << "x" << M << " outcomes... ";

  BarnardFast bbb( N, M, berger_boos_gamma, p_quantizer_steps, alpha );
  vector< vector< bool > > test_result( N + 1, vector< bool >( M + 1 ) );

  for ( unsigned int i = 0; i <= N; i++ ) {
    for ( unsigned int j = 0; j <= M; j++ ) {
      test_result.at( i ).at( j ) = bbb.p_value( i, j ) < alpha;
    }
  }

  cerr << "done." << endl << "Printing curve of false positive probabilities... ";

  for ( breal p = 0.0; p <= 1.0; p += 1.0 / p_quantizer_steps ) {
    breal false_positive_probability = 0.0;

    const breal log_p = log( p ), log_oneminusp = log( 1 - p );

    for ( unsigned int i = 0; i <= N; i++ ) {
      const breal prob_of_i = bicoln( N, i ) + i * log_p + (N - i) * log_oneminusp;
      for ( unsigned int j = 0; j <= M; j++ ) {
	if ( test_result.at( i ).at( j ) ) {
	  const breal prob_of_j = bicoln( M, j ) + j * log_p + (M - j) * log_oneminusp;
	  false_positive_probability += exp( prob_of_i + prob_of_j );
	}
      }
    }

    cout << p << " " << false_positive_probability << endl;
  }

  cerr << "done." << endl;

  return EXIT_SUCCESS;
}
