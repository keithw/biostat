#include <stdio.h>

#include "clopper-pearson.hh"

int main( void )
{
  ClopperPearson cp( 2134, 0.05 );

  Interval lim = cp.limits( 19 );

  printf( "[%Lf %Lf]\n", lim.lower, lim.upper );
}
