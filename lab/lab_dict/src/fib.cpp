/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    //return 0;
    if (n == 1 || n==0)
        return n;
    return fib(n - 1) + fib(n - 2);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    //return 0;
    static map<unsigned long, unsigned long> memo = {{0, 0}, {1, 1}};

    auto lookup = memo.find(n);
    if (lookup != memo.end())
        return lookup->second;

    memo[n] = memoized_fib(n - 1) + memoized_fib(n - 2);
    return memo[n];
}
