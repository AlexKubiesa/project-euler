// Problem050.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

const int NOT_FOUND{ -1 };

std::vector<int> getPrimes(int upperBound);
int getPrimeSumPrime(const std::vector<int>& primes, int nTerms);
int getPrimeSumPrimeFromStart(const std::vector<int>& primes, int nTerms);

int main()
{
    while (true)
    {
        int upperBound;

        std::cout << "Upper bound: ";
        std::cin >> upperBound;

        auto primes{ getPrimes(upperBound) };

        int nTerms{ 1 };
        int maxNTerms{ 1 };
        int primeSumPrime;

        while (nTerms <= primes.size())
        {
            primeSumPrime = getPrimeSumPrimeFromStart(primes, nTerms);

            if (primeSumPrime != NOT_FOUND)
            {
                std::cout << "Prime sum for " << nTerms << " terms: " << primeSumPrime << std::endl;
                maxNTerms = nTerms;
            }

            ++nTerms;
        }

        nTerms = maxNTerms + 1;
        while (nTerms <= primes.size())
        {
            primeSumPrime = getPrimeSumPrime(primes, nTerms);

            if (primeSumPrime != NOT_FOUND)
                std::cout << "Prime sum for " << nTerms << " terms: " << primeSumPrime << std::endl;

            ++nTerms;
        }
    }
}

std::vector<int> getPrimes(int upperBound)
{
    std::vector<int> primes{};

    for (int x{ 2 }; x < upperBound; ++x)
    {
        bool foundDivisor{ false };

        for (int prime : primes)
        {
            if (x % prime == 0)
            {
                foundDivisor = true;
                break;
            }
        }

        if (!foundDivisor)
            primes.push_back(x);
    }

    return primes;
}

int getPrimeSumPrime(const std::vector<int>& primes, int nTerms)
{
    if (nTerms > primes.size())
        return NOT_FOUND;
    
    int sum{ 0 };
    int primeIndex{ 0 }; // The index of the next prime to add to the sum.
    int largestPrime{ primes.back() };

    // Populate all primes in the sum except the last.
    while (primeIndex < nTerms - 1)
    {
        sum += primes[primeIndex];
        assert(sum > 0);

        // If the sum is too large, then we're not interested.
        if (sum > largestPrime)
            return NOT_FOUND;

        ++primeIndex;
    }

    while (primeIndex < primes.size())
    {
        // Populate the last prime in the sum.
        sum += primes[primeIndex];
        assert(sum > 0);

        // If the sum is too large, then we're not interested.
        if (sum > largestPrime)
            return NOT_FOUND;

        // Check whether the sum is prime.
        if (std::find(primes.begin(), primes.end(), sum) != primes.end())
        {
            return sum;
        }

        // Remove the first prime in the sum.
        sum -= primes[primeIndex - nTerms + 1];

        // Consider the next prime.
        ++primeIndex;
    }

    return NOT_FOUND;
}

int getPrimeSumPrimeFromStart(const std::vector<int>& primes, int nTerms)
{
    if (nTerms > primes.size())
        return NOT_FOUND;

    int sum{ 0 };
    int primeIndex{ 0 }; // The index of the next prime to add to the sum.
    int largestPrime{ primes.back() };

    // Populate all primes in the sum except the last.
    while (primeIndex < nTerms - 1)
    {
        sum += primes[primeIndex];
        assert(sum > 0);

        // If the sum is too large, then we're not interested.
        if (sum > largestPrime)
            return NOT_FOUND;

        ++primeIndex;
    }

    // Populate the last prime in the sum.
    sum += primes[primeIndex];

    // Check whether the sum is prime.
    if (std::find(primes.begin(), primes.end(), sum) != primes.end())
    {
        return sum;
    }

    return NOT_FOUND;
}

