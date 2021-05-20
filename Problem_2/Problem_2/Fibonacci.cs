using System.Collections.Generic;
using System.Linq;

namespace Problem_2
{
    public static class Fibonacci
    {
        public static IEnumerable<int> GetFibonacciSequence()
        {
            int x = 0;
            yield return x;

            int y = 1;
            yield return y;

            while (true)
            {
                checked
                {
                    (x, y) = (y, x + y);
                }

                yield return y;
            }
        }

        public static int GetSumOfEvenValuedTerms(int valueLimit)
        {
            return GetFibonacciSequence().Where(x => x % 2 == 0).TakeWhile(x => x <= valueLimit).Sum();
        }
    }
}