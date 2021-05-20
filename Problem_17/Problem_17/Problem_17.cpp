// Problem017.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

int cumulativeNumberNameCount(int max);
int countLetters(std::string str);
std::string getName(int number);
std::string getNameForTensAndUnits(int tensAndUnits);
std::string getDigitName(int units);
std::string getNameForTeens(int tensAndUnits);
std::string getNameForTens(int tensAndUnits);

int main()
{
    std::string numberString{};

    while (true)
    {
        std::cout << "Number: ";
        std::cin >> numberString;

        int number{ std::stoi(numberString) };
        std::string name{ getName(number) };
        int letterCount{ countLetters(name) };
        int cumulCount{ cumulativeNumberNameCount(number) };

        std::cout << name << std::endl;
        std::cout << letterCount << std::endl;
        std::cout << cumulCount << std::endl;
    }
}

int cumulativeNumberNameCount(int max)
{
    int count{};

    for (int number = 1; number <= max; ++number)
    {
        std::string name{ getName(number) };
        count += countLetters(name);
    }

    return count;
}

int countLetters(std::string str)
{
    return std::count_if(str.begin(), str.end(), [](unsigned char c) { return std::isalpha(c); });
}

std::string getName(int number)
{
    if (number <= 0)
        throw std::invalid_argument("Number must be positive.");

    if (number > 1000)
        throw std::invalid_argument("Number was too large.");

    if (number == 1000)
        return "one thousand";

    if (number < 100)
        return getNameForTensAndUnits(number);

    auto numberDiv100{ std::div(number, 100) };

    std::string name{};

    name.append(getDigitName(numberDiv100.quot));
    name.append(" hundred");

    if (numberDiv100.rem == 0)
    {
        return name;
    }

    name.append(" and ");
    name.append(getNameForTensAndUnits(numberDiv100.rem));
    
    return name;
}

std::string getNameForTensAndUnits(int tensAndUnits)
{
    if (tensAndUnits <= 0)
        throw std::invalid_argument("Number must be positive.");

    if (tensAndUnits < 10)
        return getDigitName(tensAndUnits);

    if (tensAndUnits < 20)
        return getNameForTeens(tensAndUnits);

    std::string name{};

    auto numberDiv10{ std::div(tensAndUnits, 10) };
    name.append(getNameForTens(numberDiv10.quot));

    if (numberDiv10.rem != 0)
    {
        name.append(" ");
        name.append(getDigitName(numberDiv10.rem));
    }

    return name;
}

std::string getDigitName(int digit)
{
    switch (digit)
    {
    case 1:
        return "one";
    case 2:
        return "two";
    case 3:
        return "three";
    case 4:
        return "four";
    case 5:
        return "five";
    case 6:
        return "six";
    case 7:
        return "seven";
    case 8:
        return "eight";
    case 9:
        return "nine";
    default:
        throw std::invalid_argument("Digit must be between 1 and 9.");
    }
}

std::string getNameForTeens(int tensAndUnits)
{
    switch (tensAndUnits)
    {
    case 10:
        return "ten";
    case 11:
        return "eleven";
    case 12:
        return "twelve";
    case 13:
        return "thirteen";
    case 14:
        return "fourteen";
    case 15:
        return "fifteen";
    case 16:
        return "sixteen";
    case 17:
        return "seventeen";
    case 18:
        return "eighteen";
    case 19:
        return "nineteen";
    default:
        throw std::invalid_argument("Number must be between 10 and 19.");
    }
}

std::string getNameForTens(int tens)
{
    switch (tens)
    {
    case 2:
        return "twenty";
    case 3:
        return "thirty";
    case 4:
        return "forty";
    case 5:
        return "fifty";
    case 6:
        return "sixty";
    case 7:
        return "seventy";
    case 8:
        return "eighty";
    case 9:
        return "ninety";
    default:
        throw std::invalid_argument("Tens digit must be between 2 and 9.");
    }
}

