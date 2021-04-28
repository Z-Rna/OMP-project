#pragma once
#include "fun.h"

namespace domain {
	static int IT;
	std::vector<int> primes(int start, int end, bool printOutput = true);
	std::vector<int> primesNaive(int start, int end, bool printOutput = true);
	std::vector<int> basicSieve(int start, int end, bool printOutput = true);
	std::vector<int> optimizedSive(int start, int end, bool printOutput = true);
	int* optimizedSiveDynamic(int start, int end, bool printOutput = true);
	int* primesDynamic(int start, int end, bool printOutput = true);
	void printValues(int* arr);
}

