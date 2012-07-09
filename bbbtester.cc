#include <stdio.h>

#include "barnardbb.hh"
#include "blyth-still-casella.hh"
#include "clopper-pearson.hh"

int main( void )
{
  Barnard bbb( 1000, 1000, 0.05, 0.000001 );

  printf( "p = %.20f\n", bbb.p_value( 212, 225 ) );

  return 0;
}
