#include <cstdio>

#include "clopper-pearson.hh"

int main( void )
{
  ClopperPearson cp( 2134, 0.05 );

  Interval lim = cp.limits().limits[ 19 ];

  printf( "          [%f %f]\n", lim.lower, lim.upper );

  printf( "StatXact: [0.005369 0.01387]\n" );
}
