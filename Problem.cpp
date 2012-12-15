#include "Problem.h"

#include <iostream>
#include <fstream>
#include <sstream>

Problem::Problem() : evs(), population() {
}

Problem::~Problem() {
}

void Problem::add_event(const Event ev) {
    evs.push_back(ev);
}

void Problem::add_from_path(const std::string& path) {
    std::ifstream in(path);
    add_from_stream(in);
}

void Problem::add_from_stream(const std::istream& in) {
    while (in.good()) {
        break;
    }
}

void Problem::add_from_string(const std::string& str) {
    std::stringstream ss(str);
    add_from_stream(ss);
}

void Problem::add_from_vector(const std::vector<Event>& vec) {
    evs.insert(evs.end(), vec.begin(), vec.end());
}

// Returns the amount events in this problem
size_t Problem::size() const {
    return evs.size();
}

// High-level "Go solve this thing" function
Solution Problem::solve() {
    std::array<pick_t, MAX_EVENTS> max;
    max.fill(0);
    for (size_t i = 0; i < evs.size(); i++) {
        max[i] = evs[i].starts.size() - 1;
    }
    population.max_picks = max;
    population.evs = evs.size();

    population.populate();

    int gens = 1;
    while (true) {
        //std::cout << "   Generation #" << gens << " (best: " << population.best().fitness << ")" << std::endl;
        population.select(this);
        if (gens >= GENS_COUNT) break;
        population.crossover();
        population.mutate();
        gens++;
    }

    return population.best();
}

// High-level "Print this to somewhere" function
void Problem::format(std::ostream& out) {
    out << "  Dump of problem " << this << ":" << std::endl;

    if (size() == 0) {
        out << "  No events." << std::endl;
    } else {
        for (Event ev : evs) {
            out << "e ";
            out << ev.description;
            out << " (" << ev.length << ")";

            for (block_t start : ev.starts) {
                out << " " << start;
            }

            out << std::endl;
        }
    }
}
