using System;

namespace Problem_2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine($"The answer is: {Fibonacci.GetSumOfEvenValuedTerms(4_000_000)}");
            Console.ReadLine();
        }
    }
}
