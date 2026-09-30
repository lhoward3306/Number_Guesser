#include "../game_logic.h"

#include <cassert>
#include <random>

int main() {
    assert(parseYesNo("y") == YesNo::Yes);
    assert(parseYesNo("Yes") == YesNo::Yes);
    assert(parseYesNo("NO") == YesNo::No);
    assert(parseYesNo("maybe") == YesNo::Invalid);
    assert(parseYesNo("y e s") == YesNo::Invalid);

    assert(parseDirection("h") == Direction::Higher);
    assert(parseDirection("HIGHER") == Direction::Higher);
    assert(parseDirection("l") == Direction::Lower);
    assert(parseDirection("Lower") == Direction::Lower);
    assert(parseDirection("sideways") == Direction::Invalid);
    assert(parseDirection("high er") == Direction::Invalid);

    Range higherRange{0, 100};
    updateRange(higherRange, 42, Direction::Higher);
    assert(higherRange.minimum == 43);
    assert(higherRange.maximum == 100);

    Range lowerRange{0, 100};
    updateRange(lowerRange, 42, Direction::Lower);
    assert(lowerRange.minimum == 0);
    assert(lowerRange.maximum == 41);

    Range contradiction{0, 0};
    updateRange(contradiction, 0, Direction::Lower);
    assert(!isValid(contradiction));

    std::mt19937 generator(1234);
    const Range fixedRange{100, 100};
    assert(randomGuess(fixedRange, generator) == 100);

    const Range randomRange{10, 20};
    for (int count = 0; count < 100; ++count) {
        const int guess = randomGuess(randomRange, generator);
        assert(guess >= randomRange.minimum);
        assert(guess <= randomRange.maximum);
    }
}
