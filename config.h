#pragma once

#include <limits>
#include <cstdint>
#include <string>

// Version information
static const int MAJOR_VERS = 0;
static const int MINOR_VERS = 1;
#ifdef BUILDDATE
static std::string DATE = BUILDDATE;
#else
static std::string DATE = "unknown";
#endif
#ifdef BUILDREV
static std::string REVISION = BUILDREV;
#else
static std::string REVISION = "unknown";
#endif

// The number of threads to use.
static const int NUMTHREADS = 4;

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

// Whether or not to keep history.
static const bool KEEP_HIST = true;

// The 'pick' type: an index into a starts array.
typedef uint16_t pick_t;

// The 'block' type: a time block.
typedef uint16_t block_t;

// The highest possible block number.
// Since we use 1 block per 5 minutes and we want to schedule a week, we have
// 12 * 24 * 7 = 2016 blocks. We round up to 2048 blocks.
static const block_t MAXBLOCK = 2048;
