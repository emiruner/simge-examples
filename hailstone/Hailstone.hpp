#ifndef HAILSTONE_HPP_INCLUDED
#define HAILSTONE_HPP_INCLUDED

/**
 * Calculate f(x).
 */
long hailstone(long x);

/**
 * Calculate f(f(...f(x)))
 */
long hailstoneN(long x, long n);

/**
 * Calculate maximum value and number of steps to reach to one.
 */
void calculateRanges(long x, long& maxVal, long& maxSteps);

#endif
