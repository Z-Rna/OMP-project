#include "fun.h"

bool isPrime(int p)
{
	int div = 2;
	double sqrtP = (int)sqrt(p) + 1;

	for (; div < sqrtP; ++div){ 
		if(p % div == 0) 
			return false;
	}

	return true;
}

void period(clock_t start, clock_t stop)
{
	double period = ((double)stop - (double)start)/1000.0;
	std::cout << "Period: " << period << std::endl;
}

void printValues(std::vector<int> result)
{
	for (int r : result)
		std::cout << r << std::endl;
}
