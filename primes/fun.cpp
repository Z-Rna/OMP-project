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

void compareVectors(std::vector<int> v1, std::vector<int> v2)
{
	if (v1.size() != v2.size())
		std::cout << "string are not the same!: length error" << std::endl;
	else {
		for (size_t i = 0; i < v1.size(); i++)
		{
			if (v1[i] != v2[i]) {
				std::cout << "string are not the same! compare error " << std::endl;
				break;
			}
			
		}
	}
}
