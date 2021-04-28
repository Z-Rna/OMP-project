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
    for (int i = 0; i < threadsCount; i++) privateResults[i].reserve(end - start + 1);
#pragma omp parallel
    {
#pragma omp for
        for (int i = start; i <= end; i++)
        {
            if (isPrime(i)) privateResults[omp_get_thread_num()].push_back(i);
        }
    }
    for (size_t i = 0; i < threadsCount; i++) result.insert(result.end(), privateResults[i].begin(), privateResults[i].end());

    timeStop = omp_get_wtime();
    if (printOutput) period(timeStart, timeStop, "funcional::primes");

    return result;
}

std::vector<int> domain::primesNaive(int start, int end, bool printOutput)
{
    int size = end - start + 1;
    std::vector<int> result;
    double timeStart, timeStop;

    result.reserve(size);
    timeStart = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for
        for (int i = start; i <= end; i++)
        {
            if (isPrime(i)) result.push_back(i);
        }
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
#pragma omp for
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
    std::vector<std::vector<bool>> isPrime(threadsCount, std::vector<bool>(end + 1, false));
    /*for (int i = 0; i < threadsCount; i++) {
        isPrime[i] = std::vector<bool>(end + 1, false);
    }*/
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

int* domain::optimizedSiveDynamic(int start, int end, bool printOutput)
{
    double timeStart, timeStop;
    int upperBound = int(sqrt(end));
    int* primes2 = domain::primesDynamic(2, upperBound, false);
    

    int threadsCount = omp_get_max_threads();
    bool** isPrime = new bool * [threadsCount];
    for (int i = 0; i < threadsCount; i++) {
        isPrime[i] = new bool[end + 1]{ false };
    }

    timeStart = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (int i = 0; i < IT; i++) {
            int multiply = primes2[i] * 2;

            while (multiply <= end) {
                isPrime[omp_get_thread_num()][multiply] = true;

                multiply += primes2[i];
            }
        }
    }
    int* result = new int[end - start + 1];
    int it = 0;
    for (int i = start; i <= end; i++)
    {
        int sum = false;
        for (int j = 0; j < threadsCount; j++) {
            sum |= isPrime[j][i];
        }
        if (!sum) {
            result[it] = i;
            it++;
        }
    }
    timeStop = omp_get_wtime();
    period(timeStart, timeStop, "domain::optimizedSiveDynamic");
    int* final = new int[it];
    IT = it;
    for (size_t i = 0; i < it ; i++)
    {
        final[i] =  result[i];
    }
    delete[] isPrime;
    delete[] result;
    delete[] primes2;



    return final;
}

int* domain::primesDynamic(int start, int end, bool printOutput)
{
    int size = end - start + 1;
    double timeStart, timeStop;
    int threadsCount = omp_get_max_threads();

    int* result = new int[size];
    timeStart = omp_get_wtime();

    int** privateResult = new int* [threadsCount];
    for (int i = 0; i < threadsCount; i++) {
        privateResult[i] = new int[size];
    }

    int* privateIT = new int[threadsCount]{0};
#pragma omp parallel
    {
        int it = 0;
#pragma omp for
        for (int i = start; i <= end; i++)
        {
            if (isPrime(i)) {
                privateResult[omp_get_thread_num()][privateIT[omp_get_thread_num()]] = i;
                privateIT[omp_get_thread_num()]++;
            }
        }
    }
    int it = 0;
    for (size_t i = 0; i < threadsCount; i++)
    {
        for (size_t j = 0; j < privateIT[i]; j++)
        {
            result[it] = privateResult[i][j];
            it++;
        }
    }
    timeStop = omp_get_wtime();
    if (printOutput) period(timeStart, timeStop, "domain::primesDynamic");

    delete[] privateIT;
    delete[] privateResult;
    int* final = new int[it];

    for (size_t i = 0; i < it; i++)
    {
        final[i] = result[i];
    }
    IT = it;

    return final;
}

void domain::printValues(int* arr)
{
    int x = IT;
    for (size_t i = 0; i < x; i++)
    {
        std::cout << arr[i] << " ";
        if (i % 10 == 9)
        {
            std::cout << std::endl;
        }
    }
}
