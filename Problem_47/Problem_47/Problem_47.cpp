// Problem047.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

std::vector<int> getPrimes(int upperBound);
int countDistinctPrimeFactors(int n, const std::vector<int>& primes);
std::vector<int> getDistinctPrimeFactors(int n, const std::vector<int>& primes);

int main()
{
    int upperBound;
    int consecutiveNumbers;

    std::cout << "Upper bound: ";
    std::cin >> upperBound;
    std::cout << "Consecutive numbers: ";
    std::cin >> consecutiveNumbers;

    auto primes = getPrimes(upperBound);
    int consecutiveNumbersFound = 0;
    int n = 1;

    while (consecutiveNumbersFound < consecutiveNumbers)
    {
        int primeFactors = countDistinctPrimeFactors(n, primes);

        if (primeFactors == consecutiveNumbers)
        {
            ++consecutiveNumbersFound;
            std::cout << n << std::endl;
        }
        else
        {
            consecutiveNumbersFound = 0;
        }

        ++n;
    }
}

std::vector<int> getPrimes(int upperBound)
{
    std::vector<int> primes{};
    std::vector<bool> isPrime(upperBound, true);
    isPrime[0] = false;
    isPrime[1] = false;

    int lastNumberToCheck = sqrt(upperBound);
    for (int x = 2; x <= lastNumberToCheck; ++x)
    {
        if (isPrime[x])
        {
            primes.push_back(x);
            for (int y(x * x); y < upperBound; y += x)
            {
                isPrime[y] = false;
            }
        }
    }

    for (int x = lastNumberToCheck + 1; x < upperBound; ++x)
    {
        if (isPrime[x])
        {
            primes.push_back(x);
        }
    }

    return primes;
}

int countDistinctPrimeFactors(int n, const std::vector<int>& primes)
{
    return getDistinctPrimeFactors(n, primes).size();
}

std::vector<int> getDistinctPrimeFactors(int n, const std::vector<int>& primes)
{
    std::vector<int> primeFactors{};
    int primeIndex = 0;
    int prime = primes[0];
    bool primeUsed = false;

    while (n != 1)
    {
        auto nDiv = std::div(n, prime);

        if (nDiv.rem == 0)
        {
            n = nDiv.quot;
            if (!primeUsed)
            {
                primeFactors.push_back(prime);
                primeUsed = true;
            }
        }
        else
        {
            ++primeIndex;
            prime = primes[primeIndex];
            primeUsed = false;
        }
    }

    return primeFactors;
}