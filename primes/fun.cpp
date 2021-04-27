#include "fun.h"

bool isPrime(int p)
{
	int div = 2;
	double sqrtP = sqrt(p);

	for (; div < sqrtP; ++div){ 
		if(p % div == 0) 
			return false;
	}

	return true;
}
