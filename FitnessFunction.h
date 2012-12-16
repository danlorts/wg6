#pragma once

#include <iostream>
#include "config.h"

class Population;
class Problem;

struct Interval {
    block_t begin;
    block_t end;

    Interval();
    Interval(block_t b, block_t end);

    friend std::ostream& operator<< (std::ostream &out, Interval &i);
    inline bool intersect(const Interval &other) const;
};

class SimpleFitnessFunction {
    public:
    void fitness(Population* pop, Problem* p);
};

bool operator<(const Interval &a, const Interval &b);
