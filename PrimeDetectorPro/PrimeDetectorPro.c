#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdbool.h>
#include <intrin.h>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

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
    while (RightInput)
    {
        LeftInput %= RightInput;
        LeftInput ^= RightInput ^= LeftInput ^= RightInput;
    }
    return LeftInput;
}

__forceinline bool __stdcall MillerRabinWitness(const uint64_t Number, const uint64_t OddPart, const uint64_t Shift, const uint64_t TestBase)
{
    uint64_t TestValue = PowerModulo(TestBase, OddPart, Number);
    if (TestValue == 1 || TestValue == Number - 1)
    {
        return true;
    }
    for (int K = 0; K < Shift - 1; ++K)
    {
        TestValue = MultiplyModulo(TestValue, TestValue, Number);
        if (TestValue == Number - 1)
        {
            return true;
        }
    }
    return false;
}

__forceinline bool __stdcall IsPrime(uint64_t Number)
{
    if (~Number & 1 || Number < 2)
    {
        if (Number ^ 2)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    uint64_t OddPart = Number - 1;
    uint64_t Shift = 0;
    while (~OddPart & 1)
    {
        OddPart >>= 1;
        ++Shift;
    }

    uint64_t ReducedBase;
    if (Number > 3474749660382ULL)
    {
        ReducedBase = 2 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 325 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 9375 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 28178 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 450775 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 9780504 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 1795265022 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        return true;
    }
    else if(Number> 4759123140ULL)
    {
        ReducedBase = 2 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 3 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 5 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 7 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 11 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 13 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        return true;
    }
    else
    {
        ReducedBase = 2 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 7 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        ReducedBase = 61 % Number;
        if (ReducedBase && !MillerRabinWitness(Number, OddPart, Shift, ReducedBase))
        {
            return false;
        }

        return true;
    }
}

typedef struct BasePrimeFactors
{
    uint64_t Primality[16];
    uint64_t PrimalityExponent[16];
    uint64_t PrimalityCount;
} PrimeFactors;

__forceinline PrimeFactors __stdcall PrimeFactorize(uint64_t Number)
{
    uint64_t PrimeArray[64];
    uint64_t PrimeArrayNumber = 0;

    if (~Number & 1)
    {
        *PrimeArray = 2;

        while (~Number & 1)
        {
            PrimeArray[PrimeArrayNumber] = 2;
            ++PrimeArrayNumber;

            Number >>= 1;
        }
    }

    if (IsPrime(Number))
    {
        PrimeFactors Result;

        Result.PrimalityCount = 2;
        *Result.Primality = 2;
        *Result.PrimalityExponent = PrimeArrayNumber;
        Result.Primality[1] = Number;
        Result.PrimalityExponent[1] = 1;

        return Result;
    }

    if (Number == 1)
    {
        PrimeFactors Result;

        Result.PrimalityCount = 1;
        *Result.Primality = 2;
        *Result.PrimalityExponent = PrimeArrayNumber;

        return Result;
    }

    uint64_t TemporaryFactors[16];
    *TemporaryFactors = Number;
    uint64_t TemporaryFactorsNumber = 1;
    uint64_t CurrentDecomposeNumber;

    while (TemporaryFactorsNumber)
    {
        --TemporaryFactorsNumber;
        CurrentDecomposeNumber = TemporaryFactors[TemporaryFactorsNumber];

        for (uint64_t C = 1; C < CurrentDecomposeNumber; ++C)
        {
            uint64_t X = 2;
            uint64_t Y = 2;
            uint64_t CurrentGCD = 1;

            while (CurrentGCD == 1)
            {
                X = MultiplyModulo(X, X, CurrentDecomposeNumber) + C;
                if (X >= CurrentDecomposeNumber) X -= CurrentDecomposeNumber;

                Y = MultiplyModulo(Y, Y, CurrentDecomposeNumber) + C;
                if (Y >= CurrentDecomposeNumber) Y -= CurrentDecomposeNumber;
                Y = MultiplyModulo(Y, Y, CurrentDecomposeNumber) + C;
                if (Y >= CurrentDecomposeNumber) Y -= CurrentDecomposeNumber;

                CurrentGCD = GCD((X > Y) ? (X - Y) : (Y - X), CurrentDecomposeNumber);
            }

            if (CurrentGCD != CurrentDecomposeNumber)
            {
                if (IsPrime(CurrentGCD))
                {
                    PrimeArray[PrimeArrayNumber] = CurrentGCD;
                    ++PrimeArrayNumber;
                }
                else
                {
                    TemporaryFactors[TemporaryFactorsNumber] = CurrentGCD;
                    ++TemporaryFactorsNumber;
                }
                uint64_t OtherFactor = CurrentDecomposeNumber / CurrentGCD;
                if (IsPrime(OtherFactor))
                {
                    PrimeArray[PrimeArrayNumber] = OtherFactor;
                    ++PrimeArrayNumber;
                }
                else
                {
                    TemporaryFactors[TemporaryFactorsNumber] = OtherFactor;
                    ++TemporaryFactorsNumber;
                }

                break;
            }
        }
    }

    {
        PrimeFactors Result;
        Result.PrimalityCount = 0;

        uint64_t ProcessedMark = 0xFFFFFFFFFFFFFFFFULL;

        while (1)
        {
            uint64_t Minimum = ProcessedMark;
            bool Found = false;

            for (uint64_t K = 0; K < PrimeArrayNumber; ++K)
            {
                if (PrimeArray[K] != ProcessedMark && PrimeArray[K] < Minimum)
                {
                    Minimum = PrimeArray[K];
                    Found = true;
                }
            }

            if (!Found)
            {
                break;
            }

            uint64_t Count = 0;
            for (uint64_t K = 0; K < PrimeArrayNumber; ++K)
            {
                if (PrimeArray[K] == Minimum)
                {
                    ++Count;
                    PrimeArray[K] = ProcessedMark;
                }
            }

            Result.Primality[Result.PrimalityCount] = Minimum;
            Result.PrimalityExponent[Result.PrimalityCount] = Count;
            ++Result.PrimalityCount;
        }

        return Result;
    }
}

int32_t main()
{
    uint64_t Number;
    scanf("%llu", &Number);

    LARGE_INTEGER CounterFrequency, StartCount, EndCount;
    double DurationNanoseconds;

    QueryPerformanceFrequency(&CounterFrequency);
    QueryPerformanceCounter(&StartCount);

    PrimeFactors PrimalitiesArray = PrimeFactorize(Number);

    QueryPerformanceCounter(&EndCount);
    DurationNanoseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000.0 / CounterFrequency.QuadPart;

    if (Number > 1)
    {
        printf("%lu^%lu", *PrimalitiesArray.Primality, *PrimalitiesArray.PrimalityExponent);
        for (uint64_t K = 1; K < PrimalitiesArray.PrimalityCount; ++K)
        {
            printf(" * %lu^%lu", PrimalitiesArray.Primality[K], PrimalitiesArray.PrimalityExponent[K]);
        }
    }
    else
    {
        printf("%lu", Number);
    }

    printf("\n\nTime-consuming %.3f microseconds.\n", DurationNanoseconds);

    printf("\nPress any key to exit...\n");
    _getch();

    return 0;
}
