#define _CRT_SECURE_NO_WARNINGS

#include "PrimeDetectorProCore.h"
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#pragma comment(lib, "bcrypt.lib")

#define TEST_TIMES 1000000
#define FACTORIZATION_TEST_TIMES 10000



int32_t main()
{
    LARGE_INTEGER CounterFrequency, StartCount, EndCount;
    double DurationNanoseconds;
    QueryPerformanceFrequency(&CounterFrequency);

    volatile uint64_t NullTestResult;
    uint64_t *GCDResultArray = malloc(TEST_TIMES * sizeof(uint64_t));
    bool *PrimalityResultArray = malloc(TEST_TIMES * sizeof(bool));
    PrimeFactors *FactorizationResultArray = malloc(TEST_TIMES * sizeof(PrimeFactors));

    uint64_t *RandomArray = malloc(TEST_TIMES * 8);
    BCRYPT_ALG_HANDLE Algorithm;
    BCryptOpenAlgorithmProvider(&Algorithm, BCRYPT_RNG_ALGORITHM, NULL, 0);
    NTSTATUS status = BCryptGenRandom(Algorithm, (PUCHAR)RandomArray, TEST_TIMES * sizeof(uint64_t), 0);
    BCryptCloseAlgorithmProvider(Algorithm, 0);


    printf("Start calculating.\n");

    QueryPerformanceCounter(&StartCount);

    for (uint64_t K = 0; K < TEST_TIMES; ++K)
    {
        NullTestResult = K;
    }

    QueryPerformanceCounter(&EndCount);
    DurationNanoseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000000.0 / CounterFrequency.QuadPart / TEST_TIMES;

    printf("End calculation, taking %.3f nanoseconds.\n\n", DurationNanoseconds);


    printf("Start calculating GCD.\n");

    QueryPerformanceCounter(&StartCount);

    for (uint64_t K = 0; K < TEST_TIMES; ++K)
    {
        GCDResultArray[K] = GCD(RandomArray[K], RandomArray[K + 1]);
    }

    QueryPerformanceCounter(&EndCount);
    DurationNanoseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000000.0 / CounterFrequency.QuadPart / TEST_TIMES;

    printf("End GCD calculation, taking %.3f nanoseconds.\n\n", DurationNanoseconds);


    printf("Start calculating primality.\n");

    QueryPerformanceCounter(&StartCount);

    for (uint64_t K = 0; K < TEST_TIMES; ++K)
    {
        PrimalityResultArray[K] = IsPrime(RandomArray[K]);
    }

    QueryPerformanceCounter(&EndCount);
    DurationNanoseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000000.0 / CounterFrequency.QuadPart / TEST_TIMES;

    printf("End primality calculation, taking %.3f nanoseconds.\n\n", DurationNanoseconds);


    printf("Start calculating factorization.\n");

    QueryPerformanceCounter(&StartCount);

    for (uint64_t K = 0; K < FACTORIZATION_TEST_TIMES; ++K)
    {
        FactorizationResultArray[K] = PrimeFactorize(RandomArray[K]);
    }

    QueryPerformanceCounter(&EndCount);
    DurationNanoseconds = (EndCount.QuadPart - StartCount.QuadPart) * 1000000000.0 / CounterFrequency.QuadPart / FACTORIZATION_TEST_TIMES;

    printf("End factorization calculation, taking %.3f nanoseconds.\n\n", DurationNanoseconds);


    printf("\nPress any key to exit...\n");
    _getch();

    return 0;
}
