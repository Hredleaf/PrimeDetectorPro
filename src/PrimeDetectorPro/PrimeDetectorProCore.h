#include <stdint.h>
#include <stdbool.h>
#include <intrin.h>



__forceinline uint64_t __stdcall MultiplyModulo(const uint64_t LeftInput, const uint64_t RightInput, const uint64_t Modulo)
{
    uint64_t ResultLow, ResultHigh, Remainder;
    ResultLow = _umul128(LeftInput, RightInput, &ResultHigh);
    _udiv128(ResultHigh, ResultLow, Modulo, &Remainder);
    return Remainder;
}


__forceinline uint64_t __stdcall PowerModulo(uint64_t Base, uint64_t Exponent, const uint64_t Modulo)
{
    uint64_t Result = 1;
    Base %= Modulo;
    while (Exponent)
    {
        if (Exponent & 1)
        {
            Result = MultiplyModulo(Result, Base, Modulo);
        }
        Base = MultiplyModulo(Base, Base, Modulo);
        Exponent >>= 1;
    }
    return Result;
}


__forceinline uint64_t __stdcall GCD(uint64_t LeftInput, uint64_t RightInput)
{
    if (!LeftInput)
    {
        return RightInput;
    }
    if (!RightInput)
    {
        return LeftInput;
    }

    uint64_t LeftInputShift = _tzcnt_u64(LeftInput);
    uint64_t RightInputShift = _tzcnt_u64(RightInput);

    uint64_t InputShift = (LeftInputShift > RightInputShift) ? RightInputShift : LeftInputShift;

    LeftInput >>= LeftInputShift;
    RightInput >>= RightInputShift;

    // Ensure that LeftInput is greater than RightInput.
    if (LeftInput < RightInput)
    {
        uint64_t Temporary = LeftInput;
        LeftInput = RightInput;
        RightInput = Temporary;
    }

    while (true)
    {
        LeftInput -= RightInput;

        // If LeftInput is zero, return.
        if (!LeftInput)
        {
            return RightInput <<= InputShift;
        }

        LeftInput >>= _tzcnt_u64(LeftInput);

        // Ensure that LeftInput is greater than RightInput.
        if (LeftInput < RightInput)
        {
            uint64_t Temporary = LeftInput;
            LeftInput = RightInput;
            RightInput = Temporary;
        }
    }
}


// The Primality of the First 62 Numbers.
static const bool SmallNumber[62] =
{
    // 0.
    false,
    // 1.
    false,
    // 2.
    true,
    // 3.
    true,
    // 4.
    false,
    // 5.
    true,
    // 6.
    false,
    // 7.
    true,
    // 8.
    false,
    // 9.
    false,
    // 10.
    false,
    // 11.
    true,
    // 12.
    false,
    // 13.
    true,
    // 14.
    false,
    // 15.
    false,
    // 16.
    false,
    // 17.
    true,
    // 18.
    false,
    // 19.
    true,
    // 20.
    false,
    // 21.
    false,
    // 22.
    false,
    // 23.
    true,
    // 24.
    false,
    // 25.
    false,
    // 26.
    false,
    // 27.
    false,
    // 28.
    false,
    // 29.
    true,
    // 30.
    false,
    // 31.
    true,
    // 32.
    false,
    // 33.
    false,
    // 34.
    false,
    // 35.
    false,
    // 36.
    false,
    // 37.
    true,
    // 38.
    false,
    // 39.
    false,
    // 40.
    false,
    // 41.
    true,
    // 42.
    false,
    // 43.
    true,
    // 44.
    false,
    // 45.
    false,
    // 46.
    false,
    // 47.
    true,
    // 48.
    false,
    // 49.
    false,
    // 50.
    false,
    // 51.
    false,
    // 52.
    false,
    // 53.
    true,
    // 54.
    false,
    // 55.
    false,
    // 56.
    false,
    // 57.
    false,
    // 58.
    false,
    // 59.
    true,
    // 60.
    false,
    // 61.
    true
};


__forceinline bool __stdcall IsPrime(const uint64_t Number)
{
    if (Number > 61)
    {
        if (~Number & 1)
        {
            return false;
        }

        if (!(Number % 3))
        {
            return false;
        }

        if (!(Number % 5))
        {
            return false;
        }

        if (!(Number % 7))
        {
            return false;
        }

        if (!(Number % 11))
        {
            return false;
        }

        if (!(Number % 13))
        {
            return false;
        }

        if (!(Number % 17))
        {
            return false;
        }

        if (!(Number % 19))
        {
            return false;
        }

        if (!(Number % 23))
        {
            return false;
        }

        if (!(Number % 29))
        {
            return false;
        }

        if (!(Number % 31))
        {
            return false;
        }
    }
    else
    {
        return SmallNumber[Number];
    }

    const uint64_t PreNumber = Number - 1;
    uint64_t PreShift = _tzcnt_u64(PreNumber);
    // At this point, PreShift is Shift.
    uint64_t OddPart = PreNumber >> PreShift;
    --PreShift;

    if (Number > 3474749660382ULL)
    {
    STATEMENT_G_2:
        {
            uint64_t TestValue = PowerModulo(2ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_325;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_325;
                }
            }

            return false;
        }

    STATEMENT_G_325:
        {
            uint64_t TestValue = PowerModulo(325ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_9375;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_9375;
                }
            }

            return false;
        }

    STATEMENT_G_9375:
        {
            uint64_t TestValue = PowerModulo(9375ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_28178;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_28178;
                }
            }

            return false;
        }

    STATEMENT_G_28178:
        {
            uint64_t TestValue = PowerModulo(28178ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_450775;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_450775;
                }
            }

            return false;
        }

    STATEMENT_G_450775:
        {
            uint64_t TestValue = PowerModulo(450775ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_9780504;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_9780504;
                }
            }

            return false;
        }

    STATEMENT_G_9780504:
        {
            uint64_t TestValue = PowerModulo(9780504ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_179265022;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_179265022;
                }
            }

            return false;
        }

    STATEMENT_G_179265022:
        {
            uint64_t TestValue = PowerModulo(1795265022ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_G_END;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_G_END;
                }
            }

            return false;
        }

    STATEMENT_G_END:

        return true;
    }
    else if (Number > 4759123140ULL)
    {
    STATEMENT_M_2:
        {
            uint64_t TestValue = PowerModulo(2ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_M_3;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_M_3;
                }
            }

            return false;
        }

    STATEMENT_M_3:
        {
            uint64_t TestValue = PowerModulo(3ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_M_5;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_M_5;
                }
            }

            return false;
        }

    STATEMENT_M_5:
        {
            uint64_t TestValue = PowerModulo(5ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_M_7;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_M_7;
                }
            }

            return false;
        }

    STATEMENT_M_7:
        {
            uint64_t TestValue = PowerModulo(7ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_M_11;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_M_11;
                }
            }

            return false;
        }

    STATEMENT_M_11:
        {
            uint64_t TestValue = PowerModulo(11ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_M_13;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_M_13;
                }
            }

            return false;
        }

    STATEMENT_M_13:
        {
            uint64_t TestValue = PowerModulo(13ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_M_END;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_M_END;
                }
            }

            return false;
        }

    STATEMENT_M_END:

        return true;
    }
    else
    {
    STATEMENT_S_2:
        {
            uint64_t TestValue = PowerModulo(2ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_S_3;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_S_3;
                }
            }

            return false;
        }

    STATEMENT_S_3:
        {
            uint64_t TestValue = PowerModulo(3ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_S_61;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_S_61;
                }
            }

            return false;
        }

    STATEMENT_S_61:
        {
            uint64_t TestValue = PowerModulo(61ULL, OddPart, Number);
            if (TestValue == 1 || TestValue == PreNumber)
            {
                goto STATEMENT_S_END;
            }

            for (uint64_t K = 0; K < PreShift; ++K)
            {
                TestValue = MultiplyModulo(TestValue, TestValue, Number);
                if (TestValue == PreNumber)
                {
                    goto STATEMENT_S_END;
                }
            }

            return false;
        }

    STATEMENT_S_END:

        return true;
    }
}


typedef struct BasePrimeFactors
{
    uint64_t Primality[18];
    uint64_t PrimalityExponent[18];
    uint64_t PrimalityCount;
} PrimeFactors;


// First 54 Primalities.
static const uint64_t SmallPrimalities[53] =
{
    3,
    5,
    7,
    11,
    13,
    17,
    19,
    23,
    29,
    31,
    37,
    41,
    43,
    47,
    53,
    59,
    61,
    67,
    71,
    73,
    79,
    83,
    89,
    97,
    101,
    103,
    107,
    109,
    113,
    127,
    131,
    137,
    139,
    149,
    151,
    157,
    163,
    167,
    173,
    179,
    181,
    191,
    193,
    197,
    199,
    211,
    223,
    227,
    229,
    233,
    239,
    241,
    251
};


__forceinline uint64_t Iteration(uint64_t Input, const uint64_t C, const uint64_t Modulo)
{
    uint64_t ResultLow, ResultHigh;
    ResultLow = _umul128(Input, Input, &ResultHigh);
    ResultHigh += _addcarry_u64(0, ResultLow, C, &ResultLow);
    _udiv128(ResultHigh, ResultLow, Modulo, &Input);
    return Input;
}


__forceinline PrimeFactors __stdcall PrimeFactorize(uint64_t Number)
{
    PrimeFactors Result;
    Result.PrimalityCount = 0;
    if (Number < 2)
    {
        return Result;
    }

    // Separate prime factor 2.
    if (~Number & 1)
    {
        uint64_t TemporaryExponent;
        *Result.Primality = 2;
        Result.PrimalityCount = 1;
        TemporaryExponent = _tzcnt_u64(Number);
        *Result.PrimalityExponent = TemporaryExponent;
        Number >>= TemporaryExponent;
    }

    // Small Primalities trial division.
    {
        uint64_t TemporaryPrimality;
        uint64_t TemporaryPrimalityExponent;
        for (uint64_t K = 0; K < 53; ++K)
        {
            TemporaryPrimality = SmallPrimalities[K];
            if (!(Number % TemporaryPrimality))
            {
                TemporaryPrimalityExponent = 0;
                while (!(Number % TemporaryPrimality))
                {
                    ++TemporaryPrimalityExponent;
                    Number /= TemporaryPrimality;
                }

                Result.Primality[Result.PrimalityCount] = TemporaryPrimality;
                Result.PrimalityExponent[Result.PrimalityCount] = TemporaryPrimalityExponent;
                ++Result.PrimalityCount;
            }
        }
    }

    if (IsPrime(Number))
    {
        Result.Primality[Result.PrimalityCount] = Number;
        Result.PrimalityExponent[Result.PrimalityCount] = 1;
        ++Result.PrimalityCount;
        return Result;
    }

    if (Number == 1)
    {
        return Result;
    }

    uint64_t PrimalitiesStack[16];
    uint64_t PrimalitiesStackCount = 0;
    // Separate remaining factors.
    {
        uint64_t FactorsStack[16];
        *FactorsStack = Number;
        uint64_t FactorsStackCount = 1;
        uint64_t DecomposeNumber;

        uint64_t C, X, Y, CurrentGCD;

        while (FactorsStackCount)
        {
            --FactorsStackCount;
            DecomposeNumber = FactorsStack[FactorsStackCount];

            // Pollard Rho.
            for (C = 1; C < DecomposeNumber; ++C)
            {
                X = 2;
                Y = 2;
                CurrentGCD = 1;

                while (CurrentGCD == 1)
                {
                    X = Iteration(X, C, DecomposeNumber);
                    Y = Iteration(Y, C, DecomposeNumber);
                    Y = Iteration(Y, C, DecomposeNumber);

                    if (X == Y)
                    {
                        break;
                    }

                    CurrentGCD = GCD((X > Y) ? (X - Y) : (Y - X), DecomposeNumber);
                }

                if (X == Y)
                {
                    continue;
                }

                if (CurrentGCD != DecomposeNumber)
                {
                    if (IsPrime(CurrentGCD))
                    {
                        PrimalitiesStack[PrimalitiesStackCount] = CurrentGCD;
                        ++PrimalitiesStackCount;
                    }
                    else
                    {
                        FactorsStack[FactorsStackCount] = CurrentGCD;
                        ++FactorsStackCount;
                    }

                    uint64_t OtherFactor = DecomposeNumber / CurrentGCD;
                    if (IsPrime(OtherFactor))
                    {
                        PrimalitiesStack[PrimalitiesStackCount] = OtherFactor;
                        ++PrimalitiesStackCount;
                    }
                    else
                    {
                        FactorsStack[FactorsStackCount] = OtherFactor;
                        ++FactorsStackCount;
                    }

                    break;
                }
            }
        }
    }

    // Sort primalities.
    {
        if (PrimalitiesStackCount > 1)
        {
            for (uint64_t I = 0; I < PrimalitiesStackCount - 1; ++I)
            {
                for (uint64_t J = I; J < PrimalitiesStackCount - 1; ++J)
                {
                    if (PrimalitiesStack[J] > PrimalitiesStack[J + 1])
                    {
                        uint64_t Temporary = PrimalitiesStack[J];
                        PrimalitiesStack[J] = PrimalitiesStack[J + 1];
                        PrimalitiesStack[J + 1] = Temporary;
                    }
                }
            }
        }

        Result.Primality[Result.PrimalityCount] = PrimalitiesStack[0];
        Result.PrimalityExponent[Result.PrimalityCount] = 1;
        for (uint64_t K = 1; K < PrimalitiesStackCount; ++K)
        {
            if (PrimalitiesStack[K] != Result.Primality[Result.PrimalityCount])
            {
                ++Result.PrimalityCount;
                Result.Primality[Result.PrimalityCount] = PrimalitiesStack[K];
                Result.PrimalityExponent[Result.PrimalityCount] = 1;
            }
            else
            {
                ++Result.PrimalityExponent[Result.PrimalityCount];
            }
        }
        ++Result.PrimalityCount;
    }
}
