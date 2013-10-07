#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "blyth-still-casella.hh"
#include "clopper-pearson.hh"

long int myatoi( const char *str )
{
  char *end;

  errno = 0;
  long int ret = strtol( str, &end, 10 );

  if ( ( errno != 0 )
       || ( end != str + strlen( str ) ) ) {
    fprintf( stderr, "Bad integer: %s\n", str );
    exit( 1 );
  }

  return ret;
}

double myatof( const char *str )
{
  char *end;

  errno = 0;
  double ret = strtod( str, &end );

  if ( ( errno != 0 )
       || ( end != str + strlen( str ) ) ) {
    fprintf( stderr, "Bad floating-point number: %s\n", str );
    exit( 1 );
  }

  return ret;
}

int main( int argc, char *argv[] )
{
  if ( argc != 4 ) {
    fprintf( stderr,
	     "Usage: %s NUM_TOTAL NUM_SUCCESSES CONFIDENCE\nExample: %s 40 100 0.95\n",
	     argv[ 0 ], argv[ 0 ] );
    exit( 1 );
  }

  const unsigned int num_total = myatoi( argv[ 1 ] );
  const unsigned int num_successes = myatoi( argv[ 2 ] );
  const double confidence = myatof( argv[ 3 ] );

  assert( num_total > 0 );
  //  assert( num_successes >= 0 );
  assert( num_successes <= num_total );
  assert( confidence >= 0.0 );
  assert( confidence < 1.0 );

  ClopperPearson cp( num_total, 1 - confidence );
  BlythStillCasella bsc( cp.limits() );
  Interval lim = bsc.limits( num_successes );
  Interval cplim = cp.limits().limits[ num_successes ];

  printf( "Observed %u successes in %u trials.\n", num_successes, num_total );
  printf( "Blyth-Still-Casella %.0f%% confidence interval: [%.8f %.8f]\n",
	  100 * confidence, lim.lower, lim.upper );
  printf( "Clopper-Pearson: %.0f%% confidence interval: [%.8f %.8f]\n",
	  100 * confidence, cplim.lower, cplim.upper );

  return 0;
}

/* test case: 19 / 2134 with 95% confidence */
/* StatXact gives [.005369, .01382] */
