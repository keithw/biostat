#include <stdio.h>

#include "blyth-still-casella.cc"
#include "clopper-pearson.hh"
#include "coverage-graph.cc"

typedef BlythStillCasella<ClopperPearson> BSC;

int main( void )
{
  BSC bsc( 2134, 0.05 );
  Interval lim = bsc.limits( 19 );

  fprintf( stderr, "%d BSC:          [%.10f %.10f]\n", 19, lim.lower, lim.upper );
  fprintf( stderr, "StatXact:        [.005369, .01382]\n" );

  return 0;
}
