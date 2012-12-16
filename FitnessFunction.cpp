#include "FitnessFunction.h"

#include "Problem.h"
#include "config.h"

#include <iostream>
#include <set>
#include <array>
#include <algorithm>

std::array<Interval, MAX_EVENTS> inuse;
unsigned int intervals = 0;

// Intervals are sorted by start.
inline bool operator<(const Interval &a, const Interval &b) {
    return a.begin < b.begin;
}

inline bool Interval::intersect(const Interval &other) const {
    return other.begin < end && begin < other.end;
}

Interval::Interval() {
    begin = 0;
    end = 0;
}

Interval::Interval(block_t b, block_t e) {
    begin = b;
    end = e;
}

std::ostream& operator<< (std::ostream &out, Interval &i) {
    out << "[" << i.begin << ", " << i.end << ")";
    return out;
}

void SimpleFitnessFunction::fitness(Population* pop, Problem* p) {
    //int lo, hi;
    unsigned int fitness;
    //bool allfit;

    #pragma omp parallel for private(inuse, fitness, intervals) num_threads(NUMTHREADS) 
    for (int is = 0; is < POPULATION; is++) {
        /* MAIN FITNESS DETERMINATION */
        /* Is every event scheduled on a unique time? */

        intervals = 0; // Reset inuse array
        fitness = 0; // Reset fitness

        //lo = MAXBLOCK;
        // hi = 0;
        // allfit = true;

        for (int ie = 0; ie < (int)p->evs.size(); ie++) {
            //std::cout << std::endl;

            bool fits = true;

            pick_t pick = pop->pop[is].picks[ie];
            block_t beg = p->evs[ie].starts[pick];
            block_t end = beg + p->evs[ie].length;
            Interval iv(beg, end);

            //std::cout << "  Trying event at interval " << iv << std::endl;
            //std::cout << "  Intervals in use:";

            //for (unsigned int x = 0; x < intervals; x++) {
                //std::cout << " " << inuse[x];
            //}

            //std::cout << std::endl;

            unsigned int i;
            for (i = 0; i < intervals; i++) {
                Interval other = inuse[i];

                if (iv.intersect(other)) {
                    //std::cout << "  Interval ";
                    //std::cout << iv;
                    //std::cout << " intersects ";
                    //std::cout << other;
                    //std::cout << ".";
                    //std::cout << std::endl;

                    fits = false;
                    break;
                } else {
                    //std::cout << "  Interval ";
                    //std::cout << iv;
                    //std::cout << " doesn't intersect ";
                    //std::cout << other;
                    //std::cout << ".";
                    //std::cout << std::endl;
                }
            }

            if (fits) {
                //std::cout << "  Event fits at interval " << iv << std::endl;
                fitness += 1000;
                inuse[i] = iv;
                intervals++;
            } else {
                //std::cout << "  Event doesn't fit, not awarding points" << std::endl;
                //allfit = false;
            }
        }

        // SECONDARY FITNESS DETERMINATION
        
        /*
        
        if (allfit) {
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
        }
        */

        // Save fitness
        pop->pop[is].fitness = fitness;
    }
}
