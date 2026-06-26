#define _CRT_SECURE_NO_WARNINGS

#include "PrimeDetectorProCore.h"
#include <conio.h>
#include <stdio.h>
#include <Windows.h>



int32_t main()
{
    uint64_t Number;
    scanf("%llu", &Number);


    LARGE_INTEGER CounterFrequency, StartCount, EndCount;
    double PrimalityDurationMicroseconds, FactorizationDurationMicroseconds;
    QueryPerformanceFrequency(&CounterFrequency);


    QueryPerformanceCounter(&StartCount);

    bool IsNumberPrime = IsPrime(Number);

    QueryPerformanceCounter(&EndCount);
    PrimalityDurationMicroseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000.0 / CounterFrequency.QuadPart;


    QueryPerformanceCounter(&StartCount);

    PrimeFactors PrimalitiesArray = PrimeFactorize(Number);

    QueryPerformanceCounter(&EndCount);
    FactorizationDurationMicroseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000.0 / CounterFrequency.QuadPart;


    if (IsNumberPrime)
    {
        printf("\nIt is a primality.\n");
    }
    else
    {
        printf("\nIt is not a primality.\n");
    }


    if (Number > 1)
    {
        if (*PrimalitiesArray.PrimalityExponent != 1)
        {
            printf("%llu^%llu", *PrimalitiesArray.Primality, *PrimalitiesArray.PrimalityExponent);
        }
        else
        {
            printf("%llu", *PrimalitiesArray.Primality);
        }
        for (uint64_t K = 1; K < PrimalitiesArray.PrimalityCount; ++K)
        {
            if (PrimalitiesArray.PrimalityExponent[K] != 1)
            {
                printf(" * %llu^%llu", PrimalitiesArray.Primality[K], PrimalitiesArray.PrimalityExponent[K]);
            }
            else
            {
                printf(" * %llu", PrimalitiesArray.Primality[K]);
            }
        }
    }
    else
    {
        printf("%llu", Number);
    }


    printf("\n\nCalculating primality consuming %.3f microseconds.\n", PrimalityDurationMicroseconds);
    printf("\nFactorization consuming %.3f microseconds.\n", FactorizationDurationMicroseconds);


    printf("\nPress any key to exit...\n");
    _getch();


    return 0;
}
