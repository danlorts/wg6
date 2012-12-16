#include "config.h"

static_assert(NUMTHREADS >= 1, "Need at least 1 thread");
static_assert(POPULATION >= 1, "Need a population of at least 1");
static_assert(GENS_COUNT >= 1, "Need at least 1 generation");
static_assert(MAX_EVENTS >= 1, "MAX_EVENTS should be 1 or more");
static_assert(MAXBLOCK >= 1, "MAXBLOCK should be 1 or more");

