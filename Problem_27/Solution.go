package main

import (
	"fmt"
	"math"
)

// Analysis
// ========
// The problem requires us to find a quadratic expression f(n) = n^2 + a*n + b with the highest
// number of consecutive primes, starting from n = 0.
//
// Clearly if n = 0 gives a prime, then b is prime. So, we only need to consider b prime.
//
// The question allows a and b to be negative, but doesn't clarify whether we consider negative
// numbers like -2 to be prime. I will assume -2, -3, -5 etc. are prime, since they are, from an
// Algebraic Number Theory point of view. +/- 1 are not prime (they're "units").
//
// Claim: We only need to consider n < max(|a|, |b|).
// Proof:
//     We need to show Streak(f) < max(|a|, |b|), where Streak(f) is the number of consecutive
//     prime values f(0), f(1), f(2), etc.
//
//     Suppose b > 0. f(b) = b^2 + a*b + b = b*(a + b + 1), which is composite unless b = +/- 1
//     or a + b + 1 = +/- 1. If b = +/- 1, then f(0) = b = +/- 1, so Streak(f) = 0. If
//     a + b + 1 = 1, then b = -a and f(1) = 1, so Streak(f) <= 1. If a + b + 1 = -1 then
//     b = -a - 2 and f(1) = -1, so Streak(f) <= 1. So, for b > 0, Streak(f) < |b|.
//
//     Now suppose b < 0. f(-b) = b^2 - a*b + b = b*(-a + b + 1), which is composite unless
//     b = +/- 1 or -a + b + 1 = +/- 1. If b = +/- 1, then f(0) = +/- 1, so Streak(f) = 0. If
//     -a + b + 1 = 1, then b = a and f(a) = a^2 + a^2 + a = a*(2*a + 1). This is composite
//     assuming f(0) = a is prime, because it means a <= -2 and 2*a + 1 <= -3. So Streak(f) < |a|.
//     If -a + b + 1 = -1, then b = a - 2 and f(a - 2) = (a - 2)^2 + a*(a - 2) + a - 2
//     = (a - 2)*(2*a - 1). This is composite assuming f(0) = a - 2 is prime, since it means
//     a - 2 <= -2 and 2*a - 1 <= -3. So Streak(f) < |a|.
//
//     QED.
//
// Claim: We only need to consider |f(n)| <= 2,000,000.
// Proof:
//     We know we only need to consider n < max(|a|, |b|), and |a| < 1,000 and |b| <= 1,000. So,
//     |f(n)|  = |n^2 + a*n + b|
//            <= |n|^2 + |a|*|n| + |b|
//            <= 1,000,000 + (1,000 - 1)*1,000 + 1,000
//             = 1,000,000 + 1,000,000 - 1,000 + 1,000
//             = 2,000,000.
//     QED.

const SieveSize = 2_000_000
const MaxA = 1_000 - 1
const MaxB = 1_000

// A prime number sieve, where the value at index i says whether i is prime. 0 and 1 are not prime.
type Sieve []bool

// Uses a sieve to check whether a number is prime.
func (sieve Sieve) IsPrime(x int) bool {
	if x > 0 {
		return sieve[x]
	}
	return sieve[-x]
}

// Creates a Sieve of Eratosthenes up to the given number. The sieve has length (max + 1) and
// records the primality of the numbers 0 to max.
func SieveOfEratosthenes(max int) *Sieve {
	// Allocate sieve.
	sieve := Sieve(make([]bool, max+1))
	// Initialise values to true for i >= 2.
	for i := 2; i <= max; i++ {
		sieve[i] = true
	}
	// Set composite values to false.
	sqrtMax := int(math.Sqrt(float64(max)))
	for i := 2; i <= sqrtMax; i++ {
		if sieve[i] {
			for j := i * i; j <= max; j += i {
				sieve[j] = false
			}
		}
	}
	return &sieve
}

// A formula of the form n^2 + a*n + b, where n = 0, 1, 2, etc.
type Formula struct {
	a, b int
}

func (f Formula) String() string {
	return fmt.Sprintf("n^2 + %v*n + %v", f.a, f.b)
}

func (f Formula) Evaluate(n int) int {
	return n*n + f.a*n + f.b
}

// Finds the number of consecutive primes f(0), f(1), f(2), etc. before a composite number is
// encountered.
func (f Formula) PrimeStreak(sieve *Sieve) int {
	for n := 0; ; n++ {
		if !sieve.IsPrime(f.Evaluate(n)) {
			return n
		}
	}
}

func BestFormula(sieve *Sieve) Formula {
	maxStreak := 0
	maxF := new(Formula)
	for a := -MaxA; a <= MaxA; a++ {
		for b := -MaxB; b <= MaxB; b++ {
			f := Formula{a, b}
			streak := f.PrimeStreak(sieve)
			if streak > maxStreak {
				maxStreak = streak
				*maxF = f
			}
		}
	}
	return *maxF
}

// Best formula: n^2 + -61*n + 971
// Product of coefficients: -59231
// Streak: 71

func main() {
	sieve := SieveOfEratosthenes(SieveSize)
	f := BestFormula(sieve)
	fmt.Printf("Best formula: %v\n", f)
	fmt.Printf("Product of coefficients: %v\n", f.a*f.b)
	fmt.Printf("Streak: %v\n", f.PrimeStreak(sieve))
}
