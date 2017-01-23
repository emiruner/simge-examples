#include "Hailstone.hpp"
#include <cassert>

namespace
{
    inline long calculate(long x)
    {
        if(x % 2)
        {
            return static_cast<long>(3) * x + static_cast<long>(1);
        }
        else
        {
            return x / static_cast<long>(2);
        }
    }
} // namespace <unnamed>

long hailstone(long x)
{
    return calculate(x);
}

long hailstoneN(long x, long n)
{
    assert(n >= 0);
    
    if(n == 0)
    {
        return x;
    }
    
    long result = calculate(x);
    
    while(--n)
    {
        result = calculate(result);
    }
    
    return result;
}

void calculateRanges(long x, long& maxVal, long& maxSteps)
{
    long current, max, count = 1;
    current = max = x;
    
    while(current != 1)
    {
        ++count;
        current = calculate(current);
        if(current > max)
        {
            max = current;
        }
    }

    maxVal = max;
    maxSteps = count;
}


