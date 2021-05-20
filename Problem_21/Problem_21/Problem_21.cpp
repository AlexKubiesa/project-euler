// Problem021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int sumAmicableNumbers(int upperBound);
bool isAmicable(int n);
int divisorSum(int n);

int main()
{
    while (true)
    {
        int upperBound{};

        std::cout << "Upper bound: ";
        std::cin >> upperBound;

        int sum{ sumAmicableNumbers(upperBound) };
        std::cout << sum << std::endl;
    }
}

int sumAmicableNumbers(int upperBound)
{
    int sum{ 0 };

    for (int n = 1; n < upperBound; ++n)
    {
        if (isAmicable(n))
        {
            sum += n;
        }
    }

    return sum;
}

bool isAmicable(int n)
{
    int divisorSumOfN{ divisorSum(n) };
    if (divisorSumOfN == n) return false;
    return divisorSum(divisorSumOfN) == n;
}

int divisorSum(int n)
{
    int sum{ 0 };

    for (int i{ 1 }; i < n; ++i)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}
