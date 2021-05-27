// Problem_668.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

// Returns a sieve of Eratosthenes up to and including the given number.
std::vector<bool> sieveOfEratosthenes(int max)
{
    // Mark all numbers prime by default.
    std::vector<bool> sieve(max + 1, true);

    // Mark 0 and 1 as not prime.
    sieve[0] = false;
    sieve[1] = false;

    const auto maxPrime = (int)std::sqrt(max);
    for (int n = 2; n <= maxPrime; ++n)
    {
        // If n is already composite, continue.
        if (!sieve[n])
            continue;

        // If n is prime, mark all multiples of n as composite. We only need
        // to consider multiple from n^2 onwards, because lower multiples of
        // n have already been marked as composite.
        for (auto m = n * n; m <= max; m += n)
        {
            sieve[m] = false;
        }
    }

    return sieve;
}

// Gets the primes less than or equal to the given number.
std::vector<int> getPrimes(int max)
{
    std::vector<int> primes;

    const auto sieve = sieveOfEratosthenes(max);
    for (int i = 0; i <= max; ++i)
    {
        if (sieve[i])
            primes.push_back(i);
    }

    return primes;
}

// Determines whether the number n is square root smooth. Requires a list of primes up to
// sqrt(n) (exclusive) or more.
bool isSquareRootSmooth(int64_t n, const std::vector<int>& primes)
{
    const auto maxPrime = (int)std::ceil(std::sqrt(n)) - 1;

    if (n == 1)
        return true;

    // Loop through all primes strictly less than sqrt(n).
    for (auto prime : primes)
    {
        // If the prime is too large, that means we've exhaused the primes less
        // than sqrt(n) and n is still not 1, so n is not square root smooth.
        if (prime > maxPrime)
            return false;

        // Divide n by the current prime as much as possible.
        while (n % prime == 0)
            n /= prime;

        // If n has been reduced to 1, that means it was composed of only primes
        // less than sqrt(n), i.e. n was square root smooth.
        if (n == 1)
            return true;
    }

    // Assume that the next prime in the list would have been at least sqrt(n),
    // which means n is not square root smooth.
    return false;
}

int countSquareRootSmoothNumbers(int64_t max, const std::vector<int>& primes)
{
    int count = 0;

    for (int64_t n = 1; n <= max; ++n)
    {
        if (isSquareRootSmooth(n, primes))
            ++count;

        if (n % 1'000'000 == 0)
            std::cout << "Processed up to " << n << std::endl;
    }

    return count;
}

int main()
{
    while (true)
    {
        std::cout << "Upper bound: ";

        int64_t max;
        std::cin >> max;

        const auto maxPrime = (int)std::ceil(std::sqrt(max)) - 1;
        const auto primes = getPrimes(maxPrime);

        const int count = countSquareRootSmoothNumbers(max, primes);
        std::cout << "Answer: " << count << std::endl;
    }
}

