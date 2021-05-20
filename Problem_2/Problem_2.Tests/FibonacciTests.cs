using System.Linq;
using NUnit.Framework;
using Problem_2;

namespace Problem_2.Tests
{
    public class FibonacciTests
    {
        [Test]
        [TestCase(0, 0)]
        [TestCase(1, 1)]
        [TestCase(2, 1)]
        [TestCase(3, 2)]
        [TestCase(4, 3)]
        [TestCase(5, 5)]
        [TestCase(6, 8)]
        [TestCase(7, 13)]
        [TestCase(8, 21)]
        public void GetFibonacciSequence_ShouldReturnCorrectValues(int index, int expectedValue)
        {
            Assert.That(Fibonacci.GetFibonacciSequence().ElementAt(index), Is.EqualTo(expectedValue));
        }

        [Test]
        [TestCase(10, 10)]
        [TestCase(20, 10)]
        [TestCase(40, 44)]
        public void GetSumOfEvenValuedTerms_ShouldReturnCorrectValues(int valueLimit, int expectedSum)
        {
            Assert.That(Fibonacci.GetSumOfEvenValuedTerms(valueLimit), Is.EqualTo(expectedSum));
        }

        [Test]
        [MaxTime(1000)]
        [TestCase(100)]
        [TestCase(1_000)]
        [TestCase(10_000)]
        [TestCase(100_000)]
        [TestCase(1_000_000)]
        [TestCase(4_000_000)]
        public void GetSumOfEvenValuedTerms_ShouldNotTakeTooLong(int valueLimit)
        {
            int _ = Fibonacci.GetSumOfEvenValuedTerms(valueLimit);
            Assert.Pass();
        }
    }
}