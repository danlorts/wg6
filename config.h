#pragma once

#include <limits>
#include <cstdint>

// The number of threads to use.
static const int NUMTHREADS = 1;

// The number of generations to calculate.
static const int GENS_COUNT = 2500;

// The population size.
static const int POPULATION = 2000;

// How many solutions to mutate per generation.
static const int MUTS_COUNT = POPULATION * 0.01;

// How many solutions to cross over per generation.
// The rest will be killed (randomized).
static const int CROSSOVERS = POPULATION * 0.5;

// Do we want to avoid gaps?
static const int GAPPENALTY = 5;

// Do we want a compact schedule?
static const int LENPENALTY = 5;

// The maximum amount of events.
static const int MAX_EVENTS = 100;

// The 'pick' type: an index into a starts array.
typedef uint16_t pick_t;

// The 'block' type: a time block.
typedef uint16_t block_t;

// The highest possible block number
static const block_t MAXBLOCK = std::numeric_limits<block_t>::max();
