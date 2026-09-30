#pragma once

#include <random>
#include <string>

enum class YesNo {
    Yes,
    No,
    Invalid,
};

enum class Direction {
    Higher,
    Lower,
    Invalid,
};

struct Range {
    int minimum;
    int maximum;
};

YesNo parseYesNo(const std::string& input);
Direction parseDirection(const std::string& input);
bool isValid(const Range& range);
void updateRange(Range& range, int guess, Direction direction);
int randomGuess(const Range& range, std::mt19937& generator);
