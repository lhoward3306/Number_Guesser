# Spec: Reverse Number Guesser

## Objective

Build a C++ terminal game in which the player silently chooses an integer from
0 through 100 and the program tries to guess it. The program deliberately
chooses each guess at random from the remaining valid inclusive range rather
than using binary search.

The player confirms a correct guess with `y` or `yes`. When a guess is not
correct, the player says whether their number is `higher`/`h` or `lower`/`l`.
After a successful round, the player can start a new round with `y` or `yes`.
All accepted responses are case-insensitive.

Success means the game always keeps guesses inside the valid range, ends a
round after confirmation, and restarts with fresh `0`–`100` bounds when asked.

## Tech Stack

- C++ (standard library only)
- Console input and output via `std::cin` and `std::cout`
- Random guesses via `std::mt19937` and `std::uniform_int_distribution`
- Existing Bash runner: `test_runner.sh`

No third-party dependencies are required or permitted for this feature without
approval.

## Commands

Run the current interactive build and application:

```bash
./test_runner.sh
```

Compile with warnings while developing:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
```

Run the compiled application:

```bash
./app
```

## Project Structure

```text
main.cpp                         Terminal game entry point and game flow
test_runner.sh                   Existing compile-and-run script
tests/                           Automated tests for non-interactive logic
specs/reverse-number-guesser.md  This specification
```

If game-state logic is separated from terminal I/O for testing, its source and
header files belong at the repository root, consistent with the current small
project layout. Tests remain in `tests/` and must be compiled separately from
the application entry point to avoid two `main` functions.

## Game Behavior

### Round start

1. Tell the player to choose an integer from 0 through 100 without entering it.
2. Set the inclusive bounds to `minimum = 0` and `maximum = 100`.
3. Generate and display a random integer within `[minimum, maximum]`.

### Guess feedback

1. Ask `Is <guess> correct?`
2. Accept `y` or `yes` in any letter case as confirmation. Congratulate the
   player and complete the round.
3. Accept `n` or `no` in any letter case as a negative response. Then ask
   whether the selected number is higher or lower than the guess.
4. Accept `higher` or `h` to set `minimum = guess + 1`.
5. Accept `lower` or `l` to set `maximum = guess - 1`.
6. Generate the next random guess only after a valid higher/lower response.

Invalid input must show a helpful prompt and leave the current bounds
unchanged. The program must not treat arbitrary input as a negative response.

### Contradictory feedback

If a valid higher/lower response makes `minimum > maximum`, the player has
provided feedback inconsistent with a number in the original range. Explain
the inconsistency and end the current round safely; do not construct a random
distribution with invalid bounds.

### Restart and exit

After a correct guess, ask `Play again?`.

- `y` or `yes` (case-insensitive) starts a new round with bounds reset to
  `0` and `100`.
- `n` or `no` (case-insensitive) exits cleanly.
- Any other input re-prompts without starting or ending a round.

## Code Style

- Use clear, descriptive names such as `minimum`, `maximum`, and `guess`.
- Keep input normalization and range updates in small functions so their
  behavior can be tested without interactive terminal input.
- Use inclusive bounds consistently.
- Avoid unnecessary classes, dependencies, persistence, or UI layers.

```cpp
if (feedback == Feedback::Higher) {
    minimum = guess + 1;
} else if (feedback == Feedback::Lower) {
    maximum = guess - 1;
}
```

## Testing Strategy

Use automated C++ tests for deterministic, non-interactive behavior and manual
terminal checks for prompt/response flow. Do not add a testing dependency
without approval; a small assertion-based test executable is sufficient for
this project.

Automated tests must cover:

- response normalization for `y`, `yes`, `Y`, `Yes`, `n`, `no`, `h`,
  `higher`, `l`, and `lower`;
- range updates after higher and lower feedback;
- boundary guesses of `0` and `100`;
- detection of an empty range after contradictory feedback; and
- each generated guess falling within the supplied inclusive bounds.

Manual checks must cover one successful round, invalid confirmation input,
invalid higher/lower input, contradictory feedback, and a restart followed by
a clean exit.

## Boundaries

### Always

- Validate every player response before changing game state.
- Keep each random guess within the current inclusive bounds.
- Run the applicable build and automated tests before committing.
- Preserve intentional random guessing; do not substitute binary search.

### Ask First

- Adding dependencies or a third-party test framework.
- Changing CI, the compiler standard, or the existing project layout beyond
  files needed for this feature.
- Adding persistent scores, attempt counts, graphics, or other game modes.

### Never

- Ask the player to reveal their chosen number.
- Generate a random number after bounds have become invalid.
- Treat invalid input as higher, lower, yes, or no.
- Commit secrets, generated binaries, or unrelated cleanup.

## Success Criteria

- [ ] A player can complete a round after selecting any integer from 0 to 100.
- [ ] Every guess is random and lies within the current valid inclusive range.
- [ ] Correctness accepts only `y`/`yes` and `n`/`no`, case-insensitively.
- [ ] Higher/lower feedback accepts only `higher`/`h` and `lower`/`l`,
      case-insensitively.
- [ ] Invalid input does not alter bounds or unintentionally end a round.
- [ ] Contradictory feedback is handled without a crash or invalid random
      distribution.
- [ ] A player can restart with `y`/`yes` and exit with `n`/`no`.
- [ ] Automated and manual verification scenarios pass.

## Implementation Outline

1. Add deterministic response parsing and range-update logic with tests.
2. Build the interactive round loop around that logic, including random guess
   generation and contradictory-feedback handling.
3. Add the completion and restart loop.
4. Run automated checks and the manual scenarios listed above.

## Open Questions

None. The feature intent and interaction rules are confirmed.
