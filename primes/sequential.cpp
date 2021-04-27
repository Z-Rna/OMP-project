#include "sequential.h"

std::vector<int> sequential::withoutSieve(int start, int end, bool printOutput){
    int size = end - start + 1;
    std::vector<int> result;
    clock_t timeStart, timeStop;

    result.reserve(size);
    timeStart = clock();
    for (size_t i = start; i <= end; ++i){
        if (isPrime(i)) {
            result.push_back(i);
        }
    }
    timeStop = clock();
    if(printOutput) period(timeStart, timeStop);

    return result;
}

std::vector<int> sequential::withSieve(int start, int end, bool printOutput)
{
    int sqrtEnd = (int)sqrt(end);
    clock_t timeStart, timeStop;

    timeStart = clock();
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

    timeStop = clock();

    if (printOutput) period(timeStart, timeStop);

    return result;


    return std::vector<int>();
}
