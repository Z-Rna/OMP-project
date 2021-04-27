#include <stdio.h>
#include <time.h>
#include <iostream>
#include "omp.h"
#include "fun.h"



int main(int argc, char* argv[])
{
	std::cout << isPrime(5) << std::endl;
	return 0;
}