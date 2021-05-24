#include "pch.h"
#include "framework.h"
#include <cassert>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include "Problem_65.Lib.h"

using namespace boost::multiprecision;

// Gets the nth continued fraction coefficient for Euler's constant e. Assumes n >= 1.
int coefficient(int n)
{
    if (n == 1) return 2;
    if (n % 3 == 0) return (n / 3) * 2;
    return 1;
}

// Gets a list of the numerators of the convergents of the continued fractions expansion of e, up to
// and including the (nMax)th. Assumes nMax >= 2.
std::vector<cpp_int> convergentNumerators(int nMax)
{
    std::vector<cpp_int> numerators(nMax + 1);
    numerators[0] = 1;
    numerators[1] = coefficient(1);
    for (int n = 2; n <= nMax; ++n)
    {
        numerators[n] = coefficient(n) * numerators[n - 1] + numerators[n - 2];
        assert(numerators[n] > 0);
    }
    return numerators;
}

// Gets the numerator of the nth convergent for the continued fraction expansion of e. Assumes n >= 0.
cpp_int convergentNumerator(int n)
{
    const auto numerators{ convergentNumerators(n) };
    return numerators[n];
}

// Gets the sum of the digits of n. Assumes n >= 1.
int digitSum(cpp_int n)
{
    int sum = 0;
    for (cpp_int q = n, r = 0; q > 0 || r > 0; divide_qr(q, cpp_int(10), q, r))
    {
        sum += int(r);
        assert(sum >= 0);
    }
    return sum;
}

