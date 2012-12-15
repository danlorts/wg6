#pragma once

#include <array>
#include <iosfwd>
#include <string>
#include <vector>

#include "config.h"

#include "Event.h"
#include "Parser.h"
#include "Population.h"
#include "Solution.h"

class Problem {
    public:
    // Constructor, destructor
    Problem();
    ~Problem();

    // Adds events from various sources
    void add_event(const Event ev);
    void add_from_path(const std::string& path);
    void add_from_stream(const std::istream& in);
    void add_from_string(const std::string& str);
    void add_from_vector(const std::vector<Event>& vec);

    // Returns the amount events in this problem
    size_t size() const;

    // High-level "Go solve this thing" function
    Solution solve();

    // High-level "Print this to somewhere" function
    void format(std::ostream& out);

    std::vector<Event> evs;

    private:
    Parser parser;
    Population population;
    std::array<SolverThread, NUMTHREADS> solvers;
};
