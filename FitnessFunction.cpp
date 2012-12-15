#include "FitnessFunction.h"

#include "Problem.h"

#include <iostream>

void SimpleFitnessFunction::fitness(Population* pop, Problem* p) {
    for (int is = 0; is < POPULATION; is++) {
        /* MAIN FITNESS DETERMINATION */
        /* Is every event scheduled on a unique time? */
        scratch.reset();

        unsigned int fitness = 0;
        int lo = scratch.size(), hi = 0;

        for (int ie = 0; ie < (int)p->evs.size(); ie++) {
            bool fits = true;

            pick_t pick = pop->pop[is].picks[ie];
            block_t block = p->evs[ie].starts[pick];
            
            for (int i = 0; i < p->evs[ie].length; i++) {
                block_t b = block + i;
                if (!scratch.test(b)) {
                    scratch.set(b);

                    if (b < lo) lo = b;
                    if (b > hi) hi = b;
                } else {
                    fits = false;
                    break;
                }
            }

            if (fits) fitness += 1000;
        }

        // SECONDARY FITNESS DETERMINATION
        
        // Gap penalty: substract points for gaps in the schedule
        if (GAPPENALTY && lo > 0) {
            int gaps = 0;

            for (int i = lo; i < hi; i++) {
                if (scratch[i-1] != scratch[i]) gaps++;
            }

            fitness -= (gaps - 2) * GAPPENALTY;
        }

        // Length penalty: substract points for overly long schedules
        if (LENPENALTY) {
            fitness -= (hi - lo) * LENPENALTY;
        }

        // Save fitness
        pop->pop[is].fitness = fitness;
    }
}
