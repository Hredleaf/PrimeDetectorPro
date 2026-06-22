#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdbool.h>
#include <intrin.h>
#include <Windows.h>
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

int32_t main()
{
    uint64_t Number;
    scanf("%llu", &Number);

    LARGE_INTEGER CounterFrequency, StartCount, EndCount;
    double DurationNanoseconds;

    QueryPerformanceFrequency(&CounterFrequency);
    QueryPerformanceCounter(&StartCount);

    bool IsNumberPrime = IsPrime(Number);

    QueryPerformanceCounter(&EndCount);
    DurationNanoseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000 / CounterFrequency.QuadPart;

    if (IsNumberPrime)
    {
        printf("It is a prime number.\n");
    }
    else
    {
        printf("It is not a prime number.\n");
    }

    printf("Time-consuming %.3f microseconds.\n", DurationNanoseconds);

    return 0;
}
