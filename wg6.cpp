#include <iostream>
#include <string>
#include <ctime>
#include <cassert>

#include <omp.h>

#include "config.h"

#include "Problem.h"
#include "FitnessFunction.h"

using std::cout;
using std::endl;

int main() {
    // Record start time
    time_t top;
    time(&top);

    // Spit out CGI headers
    cout << "Content-type: text/plain" << endl;
    cout << "Connection: close" << endl;
    cout << "Pragma: no-cache" << endl;
    cout << "Server: wg6" << endl;
    cout << endl;

    // Print banner
    cout << "        _     This is wg6, the genetic schedule solver." << endl;
    cout << "      _|_     wg6 is designed to be quite verbose. Expect"<< endl;
    cout << "  \\/\\(_|_)    lots of output." << endl;
    cout << "      _|      Run started: " << ctime(&top) << endl;

    cout << "  Build information:" << endl;
    cout << "  - Version:        " << MAJOR_VERS << "." << MINOR_VERS << endl;
    cout << "  - Build date:     " << DATE << endl;
    cout << "  - Commit:         " << REVISION << endl;
    cout << endl;

    // Print configuation
    cout << "  Configuration used:" << endl;
    cout << "  - Threads:        " << NUMTHREADS << endl;
    cout << "  - Generations:    " << GENS_COUNT << endl;
    cout << "  - Population:     " << POPULATION << endl;
    cout << "  - Mutations:      " << MUTS_COUNT << endl;
    cout << "  - Crossovers:     " << CROSSOVERS << endl;
    cout << "  - Gap penalty:    " << GAPPENALTY << endl;
    cout << "  - Length penalty: " << LENPENALTY << endl;
    cout << "  - Max events:     " << MAX_EVENTS << endl;
    cout << "  - Highest block:  " << MAXBLOCK << endl;
    cout << endl;

    // Print runtime information
    cout << "  Runtime information:" << endl;
    cout << "  - Processors:     " << omp_get_num_procs() << endl;
    cout << endl;

    std::vector<block_t> tights = { 1, 2, 3, 4 };
    std::vector<block_t> starts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };

    Event ev1("Fred", tights, 2);
    Event ev2("Hank", tights, 2);
    Event ev3("Buck", starts, 3);
    Event ev4("John", starts, 3);
    Event ev5("Jack", starts, 2);
    Event ev6("Mike", starts, 4);
    Event ev7("Dave", starts, 3);
    Event ev8("Luke", starts, 3);
    Event ev9("Eddy", starts, 3);
    Event ev10("Nick", starts, 3);

    Problem p;
    p.add_event(ev1);
    p.add_event(ev2);
    p.add_event(ev3);
    p.add_event(ev4);
    p.add_event(ev5);
    p.add_event(ev6);
    p.add_event(ev7);
    p.add_event(ev8);
    p.add_event(ev9);
    p.add_event(ev10);

    cout << "  Solving a problem with " << p.size() << " events" << endl;

    Solution s = p.solve();
    s.format(p, cout);

    // Print footer
    time_t bottom;
    time(&bottom);

    cout << endl;
    cout << "  Done " << ctime(&bottom);
    cout << "  Took " << difftime(bottom, top) << " seconds" << endl;
    cout << endl;
}
