#include "sequential.h"
#include "domain.h"



int main(int argc, char* argv[])
{
	omp_set_num_threads(4);
	int start = 2;
	int end = 600;
	std::vector<int> v = sequential::withoutSieve(start, end);
	std::vector<int> v2 = sequential::withSieve(start, end);
	//std::vector<int> v5 = domain::primes(start, end);
	//printValues(v);

	std::vector<int> v3 = domain::basicSieve(start, end);
	//printValues(v3);
	return 0;
}