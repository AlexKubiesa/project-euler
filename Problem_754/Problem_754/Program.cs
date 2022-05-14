using System.Globalization;

const long MODULUS = 1_000_000_007;

// Analysis
// ========
//
// G(n) is the product of all the g(i) with i <= n, and g(i) is the product of all j < i coprime to i.
// This means that the same number j appears multiple times for different i. The number of times j
// appears in the product G(n) is equal to the number of integers m coprime to j with j + 1 <= m <= n.
//
// Let f_j(n) be the number of integers m coprime to j with 1 <= m <= n. Then f_j(j) = phi(j) (the
// Euler totient function), and similarly the number of integers m coprime to j for j + 1 <= m <= 2j
// is phi(j), and similarly for 2j + 1 <= m <= 3j, etc. So if n = qj + r with 0 <= r < j, then
// f_j(n) = q * f_j(j) + f_j(r) = q * phi(j) + f_j(r). The exponent j should be raised to is
// f_j(n) - f_j(j) = (q - 1) * phi(j) + f_j(r).
//
// Call f_j(r) the "residual totient" of j with respect to n.

// TODO: Try generating all pairs of coprime integers using the tree algorithm.

while (true)
{
    Console.Write("n: ");
    string? nStr = Console.ReadLine();

    if (!int.TryParse(nStr, NumberStyles.AllowThousands, null, out int n))
        return;

    DateTime start = DateTime.Now;

    long G_n = ProductOfGaussFactorials(n);
    Console.WriteLine("G(n) = {0} (mod {1})", G_n, MODULUS);

    DateTime end = DateTime.Now;
    Console.WriteLine("Elapsed time: {0:mm\\:ss\\.fff}", end - start);

    Console.WriteLine();
}

static long ProductOfGaussFactorials(int n)
{
    long res = 1;

    bool[] isPrime = PrimeSieve(n);
    List<long> primes = Primes(isPrime);

    for (long m = 1; m <= n; m++)
    {
        List<long> primeFactors = PrimeFactors(m, primes);
        bool[] isCoprimeToM = CoprimeSieve(m, primeFactors);
        long exponent = ContributionExponent(m, n, isCoprimeToM);
        long mContribution = Exp(m, exponent);
        res *= mContribution;
        res %= MODULUS;
    }

    return res;
}

static bool[] PrimeSieve(long n)
{
    bool[] res = new bool[n + 1];

    for (long i = 2; i <= n; i++)
        res[i] = true;

    var pMax = (long)Math.Sqrt(n);
    for (long i = 2; i <= pMax; i++)
        for (long j = i * i; j <= n; j += i)
            res[j] = false;

    return res;
}

static List<long> Primes(bool[] isPrime)
{
    List<long> primes = new();

    for (long p = 0; p < isPrime.Length; p++)
        if (isPrime[p])
            primes.Add(p);

    return primes;
}

static bool[] CoprimeSieve(long n, List<long> primeFactors)
{
    bool[] res = new bool[n];

    for (long x = 0; x < n; x++)
        res[x] = true;

    foreach (long p in primeFactors)
        for (long x = 0; x < n; x += p)
            res[x] = false;

    return res;
}

static List<long> PrimeFactors(long n, List<long> primes)
{
    List<long> res = new();

    foreach (long p in primes)
    {
        if (p > n)
            break;

        if (n % p != 0)
            continue;

        res.Add(p);

        while (n % p == 0)
            n /= p;
    }

    return res;
}

/// <summary>
/// Calculates the exponent to which to raise m in the product G(n) of Gauss factorials. Requires a sieve for integers coprime to m.
/// </summary>
static long ContributionExponent(long m, long n, bool[] isCoprimeToM)
{
    (long q, long r) = Math.DivRem(n, m);

    long residualTotient = 0;
    for (long i = 1; i <= r; i++)
        if (isCoprimeToM[i])
            residualTotient++;

    long totient = residualTotient;
    for (long i = r + 1; i < m; i++)
        if (isCoprimeToM[i])
            totient++;

    return (q - 1) * totient + residualTotient;
}

static long Exp(long n, long k)
{
    long res = 1;

    while (k != 0)
    {
        if ((k & 1) == 1)
        {
            res *= n;
            res %= MODULUS;
        }

        k >>= 1;
        n *= n;
        n %= MODULUS;
    }

    return res;
}
