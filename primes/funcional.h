#pragma once
#include "fun.h"

namespace funcional {
	std::vector<int> primes(int start, int end, bool printOutput = true);
	std::vector<int> basicSieve(int start, int end, bool printOutput = true);
	int getStart(int a, int b, int threadIndex, int threadsCount);
	int getEnd(int a, int b, int threadIndex, int threadsCount);
}

