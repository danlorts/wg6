#pragma once

#include <array>

#include "config.h"

#include "Solution.h"
#include "SolverThread.h"

#include "FitnessFunction.h"

// A population of Solutions.
class Population {
    public:
    // Fill the Population with random values.
    void populate(int begin=0, int end=POPULATION);

    // Randomly change a small fraction of genes.
    void mutate();

    // Reproduce the top CROSSOVERS solutions.
    void crossover();

    // Sort the solutions.
    void select(Problem* p);

    // Return the best Solution so far.
    Solution best();

    Solution any(int end=POPULATION);

    std::array<pick_t, MAX_EVENTS> max_picks;
    std::array<Solution, POPULATION> pop;
    int evs;

    SimpleFitnessFunction sff;
};
