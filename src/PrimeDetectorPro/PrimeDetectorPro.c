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
