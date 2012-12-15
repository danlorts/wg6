#include "Population.h"

#include <random>
#include <algorithm>
#include <cassert>

#include <stdlib.h>

void Population::populate(int begin, int end) {
    srand(time(NULL));

    for (int is = begin; is < end; is++) {
        for (int ie = 0; ie < evs; ie++) {
            pop[is].picks[ie] = rand() % max_picks[ie];
        }
    }
}

void Population::mutate() {
    srand(time(NULL));

    for (int i = 0; i < MUTS_COUNT; i++) {
        int target_i = rand() % POPULATION;
        int victim_i = rand() % MAX_EVENTS;

        if (max_picks[victim_i] > 0) {
            pop[target_i].picks[victim_i] = rand() % max_picks[victim_i];
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
