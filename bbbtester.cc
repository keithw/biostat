#include <stdio.h>

#include "barnardbb.hh"
#include "blyth-still-casella.hh"
#include "clopper-pearson.hh"

int main( void )
{
  Barnard bbb( 1000, 1000, 1e-06 );

  printf( "p = %.20f\n", bbb.p_value( 400, 450 ) );

  return 0;
}
