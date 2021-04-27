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

void period(double start, double stop, std::string func)
{
	std::cout << func; 
	double period = stop - start;
	std::cout << " Period: " << period << std::endl;
}

void printValues(std::vector<int> result)
{
	for (int r : result)
		std::cout << r << std::endl;
}
