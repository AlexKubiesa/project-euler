// Problem_668.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/algorithm/minmax.hpp>
#include "primesieve.hpp"

// Analysis:
// =========
// We want to count all the square root smooth numbers from 1 to N = 10,000,000,000.
//
// Claim: A number n is *not* square root smooth if and only if n = pm with p prime
//     and p >= m. Moreover, given n, p is unique.
//
// Proof:
//     Suppose n is not square root smooth. Then n = pm with p >= sqrt(n) = sqrt(pm)
//     -> p^2 >= pm -> p >= m. Similarly, if p >= m then p^2 >= pm = n, so p >= sqrt(n).
//     
//     Now suppose n = p1*m1 = p2*m2. Suppose for contradiction that p1 != p2. Then
//     n = p1*p2*m, p1 >= sqrt(n), p2 >= sqrt(n). WLOG p1 > sqrt(n) (else p1 = p2).
//     Then n = p1*p2*m > sqrt(n)*sqrt(n)*m = nm, a contradiction. Hence p1 = p2.
//
//     QED.
//
// This means that to enumerate the non-square-root-smooth numbers, we just need to make
// a list of primes p and then count p, 2*p, 3*p, ..., p*p for each one. If p <= sqrt(N),
// then all of p, 2*p, ..., p*p are relevant. If p > sqrt(N), then only p, 2*p, ..., k*p
// are relevant, where k = floor(N/p).

using boost::multiprecision::uint128_t;

// Counts numbers that are *not* square root smooth, up to the given limit. Requires
// a list of primes up to max.
uint128_t countNonSquareRootSmoothNumbers(uint64_t max, const std::vector<uint64_t>& primes)
{
    uint128_t count = 0;

    for (const auto prime : primes)
    {
        const auto countForThisPrime = std::min(prime, max / prime);
        count += countForThisPrime;
    }

    return count;
}

// Counts the square root smooth numbers up to the given limit. Requires a list of
// primes up to max.
uint128_t countSquareRootSmoothNumbers(uint64_t max, const std::vector<uint64_t>& primes)
{
    // It's easier to count the non-square-root-smooth numbers and subtract that from the
    // total, rather than counting square root smooth numbers directly.
    return max - countNonSquareRootSmoothNumbers(max, primes);
}

int main()
{
    while (true)
    {
        std::cout << "Upper bound: ";

        uint64_t max;
        std::cin >> max;

        std::vector<uint64_t> primes;
        primesieve::generate_primes(max, &primes);
        const auto count = countSquareRootSmoothNumbers(max, primes);

        std::cout << "Answer: " << count << std::endl;
    }
}

