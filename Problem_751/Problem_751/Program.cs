using System.Text;

// Answer: 2.223561019313554106173177

const int SEQUENCE_LENGTH = 20;

while (true)
{
    Console.Write("Seed: ");
    string? seedStr = Console.ReadLine();

    if (!decimal.TryParse(seedStr, out decimal seed))
        return;

    string tau = GenerateNumber(seed, SEQUENCE_LENGTH);
    Console.WriteLine(tau);
    Console.WriteLine();
}

static string GenerateNumber(decimal seed, int length)
{
    decimal[] b_ = new decimal[length];

    b_[0] = seed;

    for (int i = 1; i < length; i++)
    {
        decimal b = b_[i - 1];
        decimal bFloor = Math.Floor(b);
        b_[i] = bFloor * (b - bFloor + 1);
    }

    decimal[] a_ = new decimal[length];

    for (int i = 0; i < length; i++)
        a_[i] = Math.Floor(b_[i]);

    StringBuilder sb = new();
    sb.Append(a_[0]).Append('.');

    for (int i = 1; i < length; i++)
        sb.Append(a_[i]);

    return sb.ToString();
}
