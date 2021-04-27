
#include "sequential.h"



int main(int argc, char* argv[])
{
	std::vector<int> v = sequential::withSieve(2, 64);
	printValues(v);
	return 0;
}