# Monte Carlo Engine

A C++ implementation of a Monte Carlo simulation for Risk-style battles, designed to simulate and analyze combat outcomes between two opposing armies.

## Overview

This project implements a Monte Carlo method-based battle simulator. It uses random dice rolling to simulate multiple battle scenarios and provides statistical analysis of the outcomes, including win probabilities and average losses.

## Project Structure

```
MonteCarloEngine/
├── main.cpp              # Entry point - user interaction and simulation orchestration
├── include/
│   ├── Army.hpp          # Army class - represents an army with tanks and territories
│   ├── Battle.hpp        # Battle class - handles individual battle rounds
│   ├── Dadi.hpp          # Dadi (Dice) class - random dice rolling mechanism
│   └── MonteCarlo.hpp    # Monte Carlo simulation controller
└── src/
    ├── Army.cpp          # Army implementation
    ├── Battle.cpp        # Battle round simulation logic
    ├── Dadi.cpp          # Dice rolling implementation
    └── MonteCarlo.cpp    # Monte Carlo simulation execution and statistics
```

## Architecture

### Core Classes

#### `Army`
Represents a player's army with:
- Player name
- Number of tanks (attack units)
- Territory count
- Territory tracking

**Key Methods:**
- `getTanks()` / `updateTanks()` - Manage tank count
- `getPlayer()` - Get player name
- `updateTerritori()` / `listTerritori()` - Territory management

#### `Dadi`
Dice rolling mechanism for combat resolution:
- Configurable number of faces (default: 6)
- Configurable number of dice to roll per turn (default: 3)
- Uses C++11 `<random>` for cryptographically secure random number generation

#### `Battle`
Handles single battle execution:
- Simulates dice rolls for both attacker and defender
- Sorts dice in descending order (Risk rule)
- Compares highest dice, second-highest dice, etc.
- Applies losses based on comparison results

**Combat Rules (Risk-style):**
- Attacker and defender each roll up to 3 dice
- Dice are sorted in descending order
- For each pair of dice: higher roll wins, ties favor defender
- Attacker loses when their die ≤ defender's die
- Defender loses when their die < attacker's die

#### `MonteCarlo`
Orchestrates multiple simulations:
- Runs requested number of battle simulations
- Tracks win/loss/draw statistics
- Calculates percentages and timing metrics
- Provides formatted output of results

## Compilation

```bash
g++ include/*.hpp src/*.cpp main.cpp -o main -std=c++17 
```

## Usage

```
$ ./monte_carlo_engine
Carri armati per il giocatore Nero: 10
Carri armati per il giocatore Rosso: 8
Numero di simulazioni da svolgere: 100

============== inizio simulazione N 1==============
============== inizio parita N 1==============
Attaccante:
4 3 2 
Difensore:
6 5 1 
Perdite lato attaccante: 2
Perdite lato difensore: 1
...
```

## Output

After completing simulations, the engine outputs:
- Win count and percentage for each player
- Draw/pareggio count and percentage
- Total registered simulations
- Sum of percentages (should be 100%)
- Total execution time in milliseconds

Example output:
```
Risultati di 100 simulazioni:
  - Nero (attaccante): 42 vittorie (42.0%)
  - Rosso (difensore): 55 vittorie (55.0%)
  - Pareggio: 3 volte (3.0%)

Totale simulazioni registrate: 100
Somma percentuali: 100.0%

Tempo totale impiegato: 2456 ms
```

## Design Decisions

1. **Italian Naming Convention**: Class members use Italian names (`esercito1`, `esercito2`, `sims`) following the project's educational context

2. **Risk Combat Rules**: Implements standard Risk dice mechanics with defender tie-break advantage

3. **STL Usage**: Leverages `<vector>`, `<map>`, and algorithms for data management

4. **Monte Carlo Methodology**: Uses statistical sampling to estimate battle probabilities for arbitrary army sizes

5. **The game engine assumes that each player always attacks with the maximum number of dice available**

## Dependencies

- C++17 or later
- Standard Library only (no external dependencies)


## Future Enhancements

Potential extensions could include:
- Variable dice counts based on army size
- Multiple simultaneous battles
- Network-weighted territory connections
- Detailed loss tracking per simulation
- CSV/JSON export for statistical analysis

## License

MIT