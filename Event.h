#pragma once

#include <string>
#include <vector>

#include "config.h"

struct Event {
    std::string description;
    std::vector<block_t> starts;
    int length;

    Event(std::string d, std::vector<block_t>& s, int len);
};
