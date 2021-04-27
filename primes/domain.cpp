#include "domain.h"

std::vector<int> domain::primes(int start, int end, bool printOutput)
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
    if (printOutput) period(timeStart, timeStop, "domain::primes");

    return result;
}

std::vector<int> domain::basicSieve(int start, int end, bool printOutput)
{

    double timeStart, timeStop;

    int sqrtEnd = (int)sqrt(end);
    std::vector<int> primes = domain::primes(2, sqrtEnd, false);
    std::vector<bool> isPrime(end + 1, false);
    timeStart = omp_get_wtime();

#pragma omp parallel 
    {
#pragma omp for schedule(static)
        for (int i = 0; i < primes.size(); i++)
        {
            int multiple = primes[i] * 2;

            while (multiple <= end) {
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

    if (printOutput) period(timeStart, timeStop, "domain::basicSieve");

    return result;
}

std::vector<int> domain::optimizedSive(int start, int end, bool printOutput)
{
    double timeStart, timeStop;
    int threadsCount = omp_get_max_threads();

    int sqrtEnd = (int)sqrt(end);
    std::vector<int> primes = domain::primes(2, sqrtEnd, false);
    std::vector<std::vector<bool>> isPrime(threadsCount, std::vector<bool>());
    for (int i = 0; i < threadsCount; i++) {
        isPrime[i] = std::vector<bool>(end + 1, false);
    }
    timeStart = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (int i = 0; i < primes.size(); i++)
        {
            int multiple = primes[i] * 2;
            while (multiple <= end) {
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
    period(timeStart, timeStop, "domain::optimizedSive");

    return result;
}
