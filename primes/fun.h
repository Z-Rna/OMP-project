#pragma once
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "omp.h"

bool isPrime(int p);

void period(double start, double stop, std::string func);

void printValues(std::vector<int> result);



