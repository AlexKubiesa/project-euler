#include "pch.h"
#include "CppUnitTest.h"
#include "..\Problem_65.Lib\Problem_65.Lib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Problem65Test
{
	TEST_CLASS(Problem65Test)
	{
	public:
		
		TEST_METHOD(TestCoefficient)
		{
			Assert::AreEqual(2, coefficient(1));
			Assert::AreEqual(1, coefficient(2));
			Assert::AreEqual(2, coefficient(3));
			Assert::AreEqual(1, coefficient(4));
			Assert::AreEqual(1, coefficient(5));
			Assert::AreEqual(4, coefficient(6));
			Assert::AreEqual(1, coefficient(7));
			Assert::AreEqual(1, coefficient(8));
			Assert::AreEqual(6, coefficient(9));
			Assert::AreEqual(1, coefficient(10));
		}

		TEST_METHOD(TestConvergentNumerator)
		{
			Assert::AreEqual(2, int(convergentNumerator(1)));
			Assert::AreEqual(3, int(convergentNumerator(2)));
			Assert::AreEqual(8, int(convergentNumerator(3)));
			Assert::AreEqual(11, int(convergentNumerator(4)));
			Assert::AreEqual(19, int(convergentNumerator(5)));
			Assert::AreEqual(87, int(convergentNumerator(6)));
			Assert::AreEqual(106, int(convergentNumerator(7)));
			Assert::AreEqual(193, int(convergentNumerator(8)));
			Assert::AreEqual(1264, int(convergentNumerator(9)));
			Assert::AreEqual(1457, int(convergentNumerator(10)));
		}

		TEST_METHOD(TestDigitSum)
		{
			Assert::AreEqual(1, digitSum(1));
			Assert::AreEqual(2, digitSum(2));
			Assert::AreEqual(2, digitSum(11));
			Assert::AreEqual(6, digitSum(123));
			Assert::AreEqual(10, digitSum(1111111111));
			Assert::AreEqual(16, digitSum(1030507));
			Assert::AreEqual(19, digitSum(100099));
		}
	};
}
