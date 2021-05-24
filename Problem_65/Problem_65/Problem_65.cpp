#include <iostream>
#include <cassert>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

#include "../Problem_65.Lib/Problem_65.Lib.h"

// Analysis:
// =========
// We want the sum of digits in the numerator of the 100th convergent of the continued fraction of e.
// Let the coefficients of the continued fraction be a1, a2, a3, ..., and the convergents be P1/Q1,
// P2/Q2, P3/Q3, .... Then e = [a1; a2, a3, ...] = [1; 1, 2, 1, ..., 1, 2k, 1, ...] and we want P100.
//
// Note that the coefficients and convergents are normally indexed from 0, but we have changed the
// indexing to start at 1 to fit with the question.
//
// The Pk are given by a recurrence relation:
// P0 = 1, P1 = a1, and Pk = ak*P(k-1) + P(k-2) for k >= 2.
// So, we can generate P100 according to the formula and then read off its digits to sum them.
// (Note the introduction of P0, even though the first convergent is P1/Q1).
//
// The formula for the convergent numerators is recursive, which means it could take a long time
// to evaluate without caching values. Let tk be the amount of time to calculate Pk. Let t0 = t1 = 1
// (for some unit of time), and from the formula we can estimate tk = t(k-1) + t(k-2). Then tk is the
// (k+1)th Fibonacci number, and these grow exponentially. The 101st Fibonacci number is ~5.7*10^20,
// which is huge! So, we should cache the values of the convergent numerators.
//
// Trial and error (with a tactical assert statement) shows that not even the long long data type
// manages to store the numerators fully (it fails at n = 46). So, we use Boost.

using namespace boost::multiprecision;

int main()
{
    while (true)
    {
        int n{};

        std::cout << "n: ";
        std::cin >> n;

        const cpp_int numerator{ convergentNumerator(n) };
        const cpp_int sum{ digitSum(numerator) };
        std::cout << "Answer: " << sum << std::endl;
        // For n = 100, the answer is 272.
    }
}

