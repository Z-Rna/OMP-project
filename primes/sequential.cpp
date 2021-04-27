#include "sequential.h"

std::vector<int> sequential::withoutSieve(int start, int end, bool printOutput){
    int size = end - start + 1;
    std::vector<int> result;
    double timeStart, timeStop;

    result.reserve(size);
    timeStart = omp_get_wtime();
    for (size_t i = start; i <= end; ++i){
        if (isPrime(i)) {
            result.push_back(i);
        }
    }
    timeStop = omp_get_wtime();
    if(printOutput) period(timeStart, timeStop, "sequential::withoutSieve");

    return result;
}

std::vector<int> sequential::withSieve(int start, int end, bool printOutput)
{
    int sqrtEnd = (int)sqrt(end);
    double timeStart, timeStop;

    timeStart = omp_get_wtime();
    std::vector<int> primes = sequential::withoutSieve(2, sqrtEnd, false);
    std::vector<bool> isPrime(end + 1, false);

    int primesSize = primes.size();

    for (auto& p: primes)
    {
        int multiple = p * 2;

        while (multiple <= end) {
            isPrime[multiple] = true;
            multiple += p;
        }
    }
    int size = end - start + 1;
    std::vector<int> result;

    result.reserve(size);

    for (size_t i = start; i <= end; i++)
    {
        if (!isPrime[i]) result.push_back(i);
    }

    timeStop = omp_get_wtime();

    if (printOutput) period(timeStart, timeStop, "sequential::withSieve");

    return result;


    return std::vector<int>();
}
