using System;
using System.Numerics;
using Rationals;

namespace Problem_71
{
    public static class FareySequence
    {
        public static Rational GetPreviousTerm(BigInteger sequenceIndex, Rational term)
        {
            if (sequenceIndex < 1)
            {
                throw new ArgumentOutOfRangeException(nameof(sequenceIndex), "Farey sequence index must be positive.");
            }

            term = term.CanonicalForm;

            if (term.Denominator > sequenceIndex)
            {
                throw new ArgumentException("The term does not appear in the specified Farey sequence.");
            }

            var previousTerm = Rational.Zero;
            var mediant = Mediant(previousTerm, term).CanonicalForm;

            while (mediant.Denominator <= sequenceIndex)
            {
                previousTerm = mediant;
                mediant = Mediant(previousTerm, term).CanonicalForm;
            }

            return previousTerm;
        }

        public static Rational Mediant(Rational x, Rational y)
        {
            return (Rational) (x.Numerator + y.Numerator) / (x.Denominator + y.Denominator);
        }
    }
}