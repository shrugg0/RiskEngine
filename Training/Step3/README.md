# Battle Simulator — Risk-style Battle Engine

A battle simulation engine inspired by the board game **Risk**, built in C++ to practice Object-Oriented Programming, STL.

This is a training module of [risiko-engine](../../), built as a stepping stone toward the full probabilistic engine.

## Project Structure

battle-simulator/
├── include/ # Header files (class declarations)
│ ├── Army.hpp
│ ├── Battle.hpp
│ ├── Dadi.hpp
├── src/ # Source files (implementations)
│ ├── Army.cpp
│ ├── Battle.cpp
│ ├── Dadi.cpp
├── main.cpp # Program entry point
└── main # Compiled executable


## Core Classes

### Army (`Army.hpp` / `Army.cpp`)
Represents an army with the following properties:
- **player**: player name
- **tanks**: number of active units
- **territori**: vector of controlled territories

**Main methods:**
- `getPlayer()`, `getTanks()`, `getNumberTerritori()` — getters
- `updateTanks(int)` — updates unit count
- `updateTerritori(string)` — adds a territory

### Dadi (`Dadi.hpp` / `Dadi.cpp`)
Handles dice rolling with:
- **faces**: number of faces per die (default: 6)
- **multiply**: how many dice to roll
- **Tira()**: generates uniformly distributed random results using `std::random_device` and `std::mt19937`

### Battle (`Battle.hpp` / `Battle.cpp`)
Resolves a single combat round between two armies:
- Rolls dice for both attacker and defender
- Sorts results in descending order
- Compares values pairwise (up to `min(attacker dice, defender dice)` comparisons)
- Updates unit losses on both sides based on Risk combat rules


## Game Mechanics (Inspired by Risk)

1. **Dice roll**: each army rolls a configurable number of dice (attacker: 3, defender: 2)
2. **Sorting**: results are sorted in descending order
3. **Comparison**: values are compared pairwise, one comparison per matched die
4. **Losses**:
   - If the attacker's value is **strictly greater** than the defender's → defender loses a unit
   - If the defender's value is **greater or equal** → attacker loses a unit (defender wins ties)
5. **Round result**: losses are applied to both armies; the process repeats until one army reaches zero tanks

## Build

```bash
g++ include/*.hpp src/*.cpp main.cpp -o main -std=c++17 

./main
```

## Usage Example

```cpp
Army esercito1("Nero", 10, 0);
Army esercito2("Rosso", 10, 0);

MonteCarlo simulatore(esercito1, esercito2, 10000);
simulatore.RunnaSimulazioni();
simulatore.PrintStats();

// Output:
// Il player Nero ( l'attaccante ) ha vinto il 18% delle volte
// Il player Rosso ( il difensore ) ha vinto il 82% delle volte
```

## Technical Notes

- **Libraries used**: `<iostream>`, `<vector>`, `<algorithm>`, `<random>`, `<map>`, `<chrono>`
- **Patterns used**: Object-Oriented Programming, encapsulation, composition
- **Random**: `std::random_device` + `std::mt19937`.


## License

MIT