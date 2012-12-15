#pragma once

#include <bitset>

#include "config.h"

class Population;
class Problem;

class SimpleFitnessFunction {
    public:
    void fitness(Population* pop, Problem* p);
};
