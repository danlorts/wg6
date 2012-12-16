#include "Population.h"

#include <random>
#include <algorithm>
#include <cassert>

#include <stdlib.h>

std::mt19937 rng;
std::uniform_int_distribution<uint32_t> uint_dist;

void Population::populate(int begin, int end) {
    rng.seed(time(NULL));

    for (int is = begin; is < end; is++) {
        for (int ie = 0; ie < evs; ie++) {
            pop[is].picks[ie] = uint_dist(rng) % max_picks[ie];
        }
    }
}

void Population::mutate() {
    for (int i = 0; i < MUTS_COUNT; i++) {
        int target_i = rand() % POPULATION;
        int victim_i = rand() % MAX_EVENTS;

        if (max_picks[victim_i] > 0) {
            pop[target_i].picks[victim_i] = uint_dist(rng) % max_picks[victim_i];
        }
    }
}

void Population::crossover() {
    int end = evs;
    // Kill the last POPULATION - CROSSOVERS solutions
    populate(CROSSOVERS, POPULATION);

    // Cross the rest
    for (int i = 0; i < CROSSOVERS; i++) {
        int begin = rand() % evs;
        Solution a = any(POPULATION);
        Solution b = any(POPULATION);

        std::swap_ranges(a.picks.begin() + begin, a.picks.begin() + end, b.picks.begin() + begin);
    }
}

void Population::select(Problem* p) {
    sff.fitness(this, p);
    std::sort(pop.begin(), pop.end(), better);
}

Solution Population::best() {
    return pop[0];
}

Solution Population::any(int end) {
    return pop[rand() % end];
}
