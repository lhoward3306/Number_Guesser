#!/bin/bash

set -e

g++ -std=c++17 -Wall -Wextra -pedantic tests/game_logic_tests.cpp game_logic.cpp -o game_logic_tests
./game_logic_tests

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp game_logic.cpp -o app
./app
