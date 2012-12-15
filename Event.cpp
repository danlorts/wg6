#include "Event.h"

Event::Event(std::string d, std::vector<block_t>& s, int len) : starts() {
    description = d;
    starts.insert(starts.end(), s.begin(), s.end());
    length = len;
}
