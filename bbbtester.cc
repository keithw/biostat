#include <cstdio>

#include "barnardbb.hh"
#include "blyth-still-casella.hh"
#include "clopper-pearson.hh"

int main( void )
{
  Barnard bbb( 100, 100, 1e-06 );

  printf( "p = %.20f\n", bbb.p_value( 40, 60, 1000 ) );

  return 0;
}
