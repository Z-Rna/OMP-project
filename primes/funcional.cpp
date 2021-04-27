#include "funcional.h"

std::vector<int> funcional::primes(int start, int end, bool printOutput)
{
    int size = end - start + 1;
    std::vector<int> result;
    double timeStart, timeStop;
    int threadsCount = omp_get_max_threads();

    result.reserve(size);
    timeStart = omp_get_wtime();

    std::vector<std::vector<int>> privateResults(threadsCount, std::vector<int>());
    for (int i = 0; i < threadsCount; i++) {
        privateResults[i].reserve(end - start + 1);
    }
#pragma omp parallel
    {
#pragma omp for
        for (int i = start; i <= end; i++)
        {
            if (isPrime(i)) privateResults[omp_get_thread_num()].push_back(i);
        }
    }
    for (size_t i = 0; i < threadsCount; i++)
    {
        result.insert(result.end(), privateResults[i].begin(), privateResults[i].end());
    }
    timeStop = omp_get_wtime();
    if (printOutput) period(timeStart, timeStop, "funcional::primes");

    return result;
}

std::vector<int> funcional::basicSieve(int start, int end, bool printOutput)
{
    double timeStart, timeStop;

    int sqrtEnd = (int)sqrt(end);
    std::vector<int> primes = funcional::primes(2, sqrtEnd, false);
    std::vector<bool> isPrime(end + 1, false);
    int threadsCount = omp_get_max_threads();

    timeStart = omp_get_wtime();

#pragma omp parallel 
    {
        int privateA = funcional::getStart(start, end, omp_get_thread_num(), threadsCount);
        int privateB = funcional::getEnd(start, end, omp_get_thread_num(), threadsCount);
        for (int i = 0; i < primes.size(); i++)
        {
            int multiple = primes[i] * 2;

            int expr = ((privateA - primes[i] * 2) / primes[i]) * primes[i];
            if (expr > 0) {
                multiple += expr;
            }

            while (multiple <= privateB) {
                isPrime[multiple] = true;
                multiple += primes[i];
            }
        }
    }
    int size = end - start + 1;
    std::vector<int> result;

    result.reserve(size);

    for (int i = start; i <= end; i++)
    {
        if (!isPrime[i]) {
            result.push_back(i);
        }
    }

    timeStop = omp_get_wtime();

    if (printOutput) period(timeStart, timeStop, "funcional::basicSieve");

    return result;
}

std::vector<int> funcional::optimizedSive(int start, int end, bool printOutput)
{
    double timeStart, timeStop;
    int threadsCount = omp_get_max_threads();

    int sqrtEnd = (int)sqrt(end);
    std::vector<int> primes = funcional::primes(2, sqrtEnd, false);
    std::vector<std::vector<bool>> isPrime(threadsCount, std::vector<bool>());
    for (int i = 0; i < threadsCount; i++) {
        isPrime[i] = std::vector<bool>(end + 1, false);
    }
    timeStart = omp_get_wtime();
#pragma omp parallel
    {
        int privateA = funcional::getStart(start, end, omp_get_thread_num(), threadsCount);
        int privateB = funcional::getEnd(start, end, omp_get_thread_num(), threadsCount);
        for (int i = 0; i < primes.size(); i++)
        {
            int multiple = primes[i] * 2;
            int expr = ((privateA - primes[i] * 2) / primes[i]) * primes[i];
            if (expr > 0) {
                multiple += expr;
            }

            while (multiple <= privateB) {
                isPrime[omp_get_thread_num()][multiple] = true;
                multiple += primes[i];
            }
        }
    }

    timeStop = omp_get_wtime();
    int size = end - start + 1;
    std::vector<int> result;

    result.reserve(size);
    for (int i = start; i <= end; i++)
    {
        int sum = false;
        for (int j = 0; j < threadsCount; j++)
        {
            sum |= isPrime[j][i];
        }
        if (!sum)
        {
            result.push_back(i);
        }

    }
    period(timeStart, timeStop, "funcional::optimizedSive");

    return result;
}

int funcional::getStart(int a, int b, int threadIndex, int threadsCount)
{
    return a + (b - a) / threadsCount * threadIndex;
}

int funcional::getEnd(int a, int b, int threadIndex, int threadsCount)
{
    if (threadIndex < threadsCount - 1) {
        return getStart(a, b, threadIndex, threadsCount) + (b - a) / threadsCount - 1;
    }
    else {
        return b;
    }
}
