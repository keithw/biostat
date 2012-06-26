#include <stdio.h>

#include "blyth-still-casella.cc"
#include "clopper-pearson.hh"
#include "coverage-graph.cc"

typedef BlythStillCasella<ClopperPearson> BSC;

int main( void )
{
  ClopperPearson cp( 2134, 0.05 );
  BSC bsc( 2134, 0.05 );

  for ( int i = 219; i <= 219; i++ ) {
    Interval limcp = cp.limits( i );
    Interval lim = bsc.limits( i );

    fprintf( stderr, "%d CP:           [%.10f %.10f]\n", i, limcp.lower, limcp.upper );
    fprintf( stderr, "%d BSC:          [%.10f %.10f]\n", i, lim.lower, lim.upper );
  }

  CoverageGraph<ClopperPearson> cgcp( 2134, 0.05 );
  CoverageGraph<BSC> cgbsc( 2134, 0.05 );

  for ( real p = 0; p < 1; p += 0.0001 ) {
    printf( "%.10f %.10f %.10f\n", p, cgcp.coverage_probability( p ), cgbsc.coverage_probability( p ) );
  }

  /*
  printf( "StatXact: [0.005858 0.05386]\n" );
  printf( "StatXact: [0.007339 0.05229]\n" );
  */
}
