#ifndef UTIL_HH
#define UTIL_HH

#include <vector>
#include <string>

typedef double breal;

class Interval
{
public:
  breal lower;
  breal upper;

  Interval( const breal s_lower, const breal s_upper );

  breal middle( void ) const;
  breal width( void ) const;
};

class IntervalCollection
{
private:
  const unsigned int N_;
  const breal alpha_;

public:
  std::vector<Interval> limits;

  IntervalCollection( const unsigned int s_N, const breal s_alpha )
    : N_( s_N ),
      alpha_( s_alpha ),
      limits( N_ + 1, Interval( 0, 1 ) )
  {}

  unsigned int N( void ) const { return N_; }
  breal alpha( void ) const { return alpha_; }
};

/* factorial */
breal factln( const unsigned int N );

/* binomial coefficient (N choose k) */
breal bicoln_raw( const unsigned int N, const unsigned int k );

/* prob that N draws from a binomial RV with prob p gives k successes */
breal likeln( const unsigned int N, const unsigned int k, const breal p );

/* memoized version */
breal bicoln( const unsigned int N, const unsigned int k );

/* conversion routines */
long int myatoi( const std::string & str );
double myatof( const std::string & str );

#endif
