#include "Solution.h"

#include <iostream>
#include <algorithm>
#include <bitset>

#include "Problem.h"

void Solution::format(Problem& p, std::ostream& out) {
    out << std::endl;
    out << "  Dump of solution " << this << " (score " << fitness << "):" << std::endl;

    std::bitset<MAX_EVENTS> bits;

    for (size_t ev = 0; ev < p.size(); ev++) {

        out << "  " << p.evs[ev].description << " ";

        for (int i = 0; i < p.evs[ev].starts[picks[ev]]; i++) {
            out << " ";
        }
        for (int i = 0; i < p.evs[ev].length; i++) {
            bits.set(p.evs[ev].starts[picks[ev]] + i);
            out << "#";
        }

        out << std::endl;
    }

    // Find highest bit set
    int high;
    for (high = bits.size() - 1; high > 0; high--) {
        if (bits.test(high)) break;
    }
    high++;

    // Display summary
    out << "       ";
    for (int i = 0; i < high; i++) {
        if (bits.test(i)) {
            out << "-";
        } else {
            out << " ";
        }
    }
    out << std::endl;
}

bool operator< (const Solution& one, const Solution& two) {
    return one.fitness < two.fitness;
}

bool better (const Solution& one, const Solution& two) {
    return one.fitness > two.fitness;
}
