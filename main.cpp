#include "game_logic.h"

#include <iostream>
#include <random>
#include <string>

namespace {

bool askYesNo(const std::string& question, YesNo& response) {
    std::string input;

    while (true) {
        std::cout << question;
        if (!std::getline(std::cin, input)) {
            return false;
        }

        response = parseYesNo(input);
        if (response != YesNo::Invalid) {
            return true;
        }

        std::cout << "Please enter y/yes or n/no.\n";
    }
}

bool askDirection(Direction& direction) {
    std::string input;

    while (true) {
        std::cout << "Is your number higher or lower? ";
        if (!std::getline(std::cin, input)) {
            return false;
        }

        direction = parseDirection(input);
        if (direction != Direction::Invalid) {
            return true;
        }

        std::cout << "Please enter higher/h or lower/l.\n";
    }
}

bool playRound(std::mt19937& generator) {
    Range range{0, 100};

    std::cout << "Choose a whole number from 0 to 100. Do not tell me!\n";

    while (isValid(range)) {
        const int guess = randomGuess(range, generator);
        YesNo correct;

        if (!askYesNo("Is " + std::to_string(guess) + " correct? ", correct)) {
            return false;
        }

        if (correct == YesNo::Yes) {
            std::cout << "I guessed it!\n";
            return true;
        }

        Direction direction;
        if (!askDirection(direction)) {
            return false;
        }

        updateRange(range, guess, direction);
    }

    std::cout << "Those answers conflict with a number from 0 to 100.\n";
    return false;
}

}  // namespace

int main() {
    std::mt19937 generator(std::random_device{}());

    while (playRound(generator)) {
        YesNo playAgain;

        if (!askYesNo("Play again? ", playAgain) || playAgain == YesNo::No) {
            break;
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
