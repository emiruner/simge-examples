#ifndef BASICRNG_HPP_INCLUDED
#define BASICRNG_HPP_INCLUDED

/**
 * Basic random number generator using next = (prev * a + b)
 */
class BasicRng
{
public:
    /**
     * Do not use.
     */
    BasicRng()
    {
    }
    
    /**
     * Create generator with given coefficients and starting number
     */
    BasicRng(int a, int b, int start)
    : a_(a), b_(b), start_(start), prev_(start)
    {
    }
    
    /**
     * Next randm number.
     */
    int next()
    {
        return prev_ = (prev_ * a_ + b_);
    }
    
    /**
     * Resets to the starting value.
     */
    void reset()
    {
        prev_ = start_;
    }
    
private:
    int a_;
    int b_;
    int start_;
    int prev_;
};

#endif
