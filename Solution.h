#pragma once

#include <array>

#include "config.h"

class Problem;

struct Solution {
    // Construction
    Solution() { picks.fill(0); }

    // Picks array
    std::array<pick_t, MAX_EVENTS> picks;

    // Formatting helper
    void format(Problem& p, std::ostream& out);

    // Score cache
    unsigned int fitness;
};

bool operator< (const Solution& one, const Solution& two);
bool better(const Solution& one, const Solution& two);
