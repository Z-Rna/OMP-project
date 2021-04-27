#pragma once
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "omp.h"

bool isPrime(int p);

void period(clock_t start, clock_t stop);

void printValues(std::vector<int> result);



