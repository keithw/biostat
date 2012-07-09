#include <stdio.h>

#include "barnardbb.hh"
#include "blyth-still-casella.hh"
#include "clopper-pearson.hh"

int main( void )
{
  Barnard bbb( 148, 132, 0.05, 0.001 );

  printf( "p = %.20f\n", bbb.p_value( 0, 131 ) );

  return 0;
}
