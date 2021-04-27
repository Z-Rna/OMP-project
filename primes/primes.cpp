#include "sequential.h"
#include "domain.h"
#include "funcional.h"


int main(int argc, char* argv[])
{
	omp_set_num_threads(4);
	int start = 2;
	int end = 6550;
	std::vector<int> v = sequential::withoutSieve(start, end);
	std::vector<int> v2 = sequential::withSieve(start, end);
	compareVectors(v, v2);

	std::vector<int> v3 = domain::basicSieve(start, end);
	compareVectors(v, v3);
	std::vector<int> v4 = domain::optimizedSive(start, end);
	compareVectors(v, v4);

	std::vector<int> v5 = funcional::basicSieve(start, end);
	compareVectors(v, v5);

	std::vector<int> v6 = funcional::optimizedSive(start, end);
	compareVectors(v, v6);

	//printValues(v3);
	return 0;
}