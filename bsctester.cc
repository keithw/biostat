#include <stdio.h>

#include "blyth-still-casella.hh"
#include "clopper-pearson.hh"

int main( void )
{
  BlythStillCasella bsc( ClopperPearson( 2134, 0.05 ).limits() );
  Interval lim = bsc.limits( 19 );

  fprintf( stderr, "%d BSC:          [%.10f %.10f]\n", 19, lim.lower, lim.upper );
  fprintf( stderr, "StatXact:        [.005369, .01382]\n" );

  return 0;
}
