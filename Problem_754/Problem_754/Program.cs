
using System.Globalization;

const long MODULUS = 1_000_000_007;

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

    for (long i = 1; i <= n; i++)
    {
        long g_i = GaussFactorial(i);
        res *= g_i;
        res %= MODULUS;
    }

    return res;
}

static long GaussFactorial(long n)
{
    long res = 1;

    List<long> primeFactors = PrimeFactors(n);
    bool[] isCoprime = CoprimeSieve(n, primeFactors);

    for (long x = 2; x < n; x++)
    {
        if (isCoprime[x])
        {
            res *= x;
            res %= MODULUS;
        }    
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

static List<long> PrimeFactors(long n)
{
    List<long> res = new();

    for (long p = 2; p <= n; p++)
    {
        if (n % p == 0)
            res.Add(p);

        while (n % p == 0)
            n /= p;
    }

    return res;
}

static bool Coprime(long a, long b) => HCF(a, b) == 1;

/// <summary>
/// Calculates the highest common factor of a and b. Assumes a and b are non-negative.
/// </summary>
static long HCF(long a, long b)
{
    while (b != 0)
        (a, b) = (b, a % b);

    return a;
}
