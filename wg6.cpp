#include <iostream>

#include "config.h"

#include "Problem.h"

int main() {
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

    //p.format(std::cout);

    p.solve().format(p, std::cout);
}
