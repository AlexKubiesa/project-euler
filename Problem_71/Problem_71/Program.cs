using System;
using Rationals;

namespace Problem_71
{
    class Program
    {
        static void Main(string[] args)
        {
            const int fareySequenceIndex = 1_000_000;
            var term = (Rational) 3 / 7;
            var previousTerm = FareySequence.GetPreviousTerm(fareySequenceIndex, term);
            var solution = previousTerm.Numerator;

            Console.WriteLine($"Solution: {solution}");
            Console.ReadLine();
        }
    }
}
