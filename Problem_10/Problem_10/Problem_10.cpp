// Problem010.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cassert>

long long sumPrimes(int upperBound);

int main()
{
    while (true)
    {
        int n{};

        std::cout << "n: ";
        std::cin >> n;

        long long sum{ sumPrimes(n) };
        std::cout << sum << std::endl;
    }
}

long long sumPrimes(int upperBound)
{
    std::vector<int> primes{};
    long long sum{ 0 };

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
        {
            primes.push_back(x);
            sum += x;
            assert(sum >= 0);
        }
    }

    return sum;
}
