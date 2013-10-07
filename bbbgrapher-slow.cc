#include <cmath>
#include <iostream>
#include <array>

#include "barnardbb.hh"

const unsigned int N = 10, M = 20;
const real alpha = 0.05;

using namespace std;

int main( void )
{
  Barnard bbb( N, M, 1e-06 );
  std::array< std::array< bool, M + 1 >, N + 1 > test_result;

  for ( unsigned int i = 0; i <= N; i++ ) {
    for ( unsigned int j = 0; j <= M; j++ ) {
      test_result.at( i ).at( j ) = ( bbb.p_value( i, j ) < alpha );
    }
  }

  for ( double p = 0.0; p <= 1.0; p += 0.1 ) {
    real false_positive_probability = 0.0;

    for ( unsigned int i = 0; i <= N; i++ ) {
      const real ln_prob_of_i = likeln( N, i, p );
      for ( unsigned int j = 0; j <= M; j++ ) {
	const real ln_prob_of_j = likeln( M, j, p );
	if ( test_result.at( i ).at( j ) ) {
	  false_positive_probability += std::exp( ln_prob_of_i + ln_prob_of_j );
	}
      }
    }

    cout << p << " " << false_positive_probability << endl << flush;
  }
}
