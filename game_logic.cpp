#include "game_logic.h"

#include <algorithm>
#include <cctype>

namespace {

std::string normalize(const std::string& input) {
    std::size_t first = 0;
    std::size_t last = input.size();

    while (first < last && std::isspace(static_cast<unsigned char>(input[first]))) {
        ++first;
    }
    while (last > first && std::isspace(static_cast<unsigned char>(input[last - 1]))) {
        --last;
    }

    std::string result = input.substr(first, last - first);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char character) {
        return static_cast<char>(std::tolower(character));
    });

    return result;
}

}  // namespace

YesNo parseYesNo(const std::string& input) {
    const std::string response = normalize(input);

    if (response == "y" || response == "yes") {
        return YesNo::Yes;
    }
    if (response == "n" || response == "no") {
        return YesNo::No;
    }

    return YesNo::Invalid;
}

Direction parseDirection(const std::string& input) {
    const std::string response = normalize(input);

    if (response == "h" || response == "higher") {
        return Direction::Higher;
    }
    if (response == "l" || response == "lower") {
        return Direction::Lower;
    }

    return Direction::Invalid;
}

bool isValid(const Range& range) {
    return range.minimum <= range.maximum;
}

void updateRange(Range& range, int guess, Direction direction) {
    if (direction == Direction::Higher) {
        range.minimum = guess + 1;
    } else if (direction == Direction::Lower) {
        range.maximum = guess - 1;
    }
}

int randomGuess(const Range& range, std::mt19937& generator) {
    std::uniform_int_distribution<int> distribution(range.minimum, range.maximum);
    return distribution(generator);
}
