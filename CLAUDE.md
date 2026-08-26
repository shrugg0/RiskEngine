# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

A C++17 probabilistic engine for the board game Risk. Given a full board state (players, territory ownership, tank counts), it runs Monte Carlo simulations of individual battles to estimate the win probability of each possible attack, then ranks all legal attacks by winning chance. The analyzed player is hard-coded to `"Red"` in `Core/main.cpp:20`.

## Project layout

```
Core/                 # Main engine (build/run from here)
├── include/          # Header declarations
│   ├── Engine.hpp    # Orchestration: evaluates & ranks all attacks
│   ├── GameState.hpp # Per-territory owner/tanks; legal-attack enumeration
│   ├── Board.hpp     # Territory adjacency graph (parsed from Board.txt)
│   ├── Battle.hpp    # Single combat round: dice, sorting, loss application
│   ├── MonteCarlo.hpp # Runs N simulated battles, collects win stats
│   ├── Army.hpp      # Lightweight value type: player name + tank count
│   └── Dadi.hpp      # Dice roller (std::random_device + mt19937)
├── src/              # Implementations
├── Assets/           # Data files the engine loads at runtime
│   ├── Board.txt         # Adjacency list: "Territory: neighbor, neighbor, ..."
│   ├── dataGame.txt      # Ownership/state:  "Territory: Owner, tanks"
│   └── MakarovChain/     # Alternative exact solver (validates MonteCarlo)
└── main.cpp          # Entry point — loads data, runs Engine::EvaluateAllAttacks
Training/             # Incremental learning exercises (Step1→Step4)
│   ├── Step1/         # Dice class only
│   ├── Step2/         # Army class
│   ├── Step3/         # Battle simulation
│   └── Step4/         # Full Monte Carlo (standalone copy)
```

The `Training/` steps are educational prototypes of the classes later reimplemented in `Core/`. They are standalone and not part of the main engine build. `Core/Assets/MakarovChain/` is an independent alternative algorithm (Markov-chain DP with memoization) used to cross-check the Monte Carlo results — it is not linked into the engine.

## Build & run

The engine is a single translation unit with no external dependencies. Build and run from `Core/`:

```bash
cd Core
g++ -std=c++17 main.cpp src/*.cpp -o risk_engine -I./include
./risk_engine        # will prompt for simulation count per battle
```

Input is the number of Monte Carlo simulations per attack (10000 recommended). Output is printed to stdout via `Engine::PrintResult()`, which sorts attacks by descending win probability.

Note: `MonteCarlo::SimulaBattle` prints verbose per-round battle output to stdout for every simulation; for large `nSim` this is very slow due to `usleep`. The `Dadi` class seeds its RNG with `steady_clock` and uses a `static` generator, so all `Dadi` objects share one generator instance.

## Key architecture

**Data flow:** `main.cpp` → `Board`/`GameState` load + parse their `.txt` files → `Engine::EvaluateAllAttacks` calls `GameState::getPossibleAttacks` to find all `(from, to)` pairs where the player owns `from` and an enemy owns an adjacent `to` → for each attack, `Engine::EvaluateAttack` builds two `Army` objects from current tank counts and runs a `MonteCarlo` of `nSim` `Battle` rounds → results are sorted by win probability and printed.

**Combat rules** (standard international Risk, defender wins ties): attacker may roll up to 3 dice (capped at `tanks - 1`); defender rolls up to 2 (`Battle::diceCap`, defaulted to 2). Dice are sorted descending and compared pairwise; in each pair `attacker <= defender` means the attacker loses one unit. The loop in `MonteCarlo::SimulaBattle` continues while `(attacker tanks - 1) > 0 && defender tanks > 0`.

**Design notes / things to watch:**
- `Army` is a value type copied into `Battle`/`MonteCarlo` on each evaluation; modifications during a simulation do not mutate the persisted `GameState`.
- `Engine::EvaluateAttack` constructs a fresh `Army` per attack with the *current* tank count, so sequential evaluations on the same `GameState` see consistent state (no mutation of `GameState` between attacks).
- The `Makarov` git branch holds an in-progress Markov-chain integration; main work happens on `to-implement`.

## Branch conventions

- `main` — released/stable code.
- `to-implement` — active work (this is the default branch you'll usually work on).
- `Makarov` — Markov-chain alternative implementation.
