using System;

namespace Problem_25
{
    public static class Fibonacci
    {
        /// <summary>
        /// The Golden Ratio, defined as (1 + √5) / 2.
        /// </summary>
        public const double Phi = 1.61803398874989484820458683436;

        /* We use the formula F_n = [φ^n / √5], where φ ≈ 1.618 is the Golden Ratio and [x] is the nearest integer to x.
         *
         * This gives us φ^n / √5 > 10^k ⇔ n > (k log(10) + log(5) / 2) / log(φ).
         */
        public static int GetIndexOfFirstFibonacciNumberWithAtLeastKDigits(int k)
        {
            checked
            {
                return (int)Math.Ceiling((k - 1 + Math.Log10(5.0) / 2.0) / Math.Log10(Phi));
            }
        }
    }
}