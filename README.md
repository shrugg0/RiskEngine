# RiskEngine
<div align="center">
  <img width="400" height="400" alt="LogoReadme" src="https://github.com/user-attachments/assets/0ff1680b-b6b3-42cd-b889-08ad6cec721d" />
</div>

A probabilistic engine for the board game Risk, built to compute exact battle win probabilities and suggest optimal moves.

Given full board state — players, territories, tanks per territory, and adjacent connections — the engine analytically calculates each legal attack's probability of winning using **Markov Chains** (absorbing Markov chain transitions with dynamic programming and memoization), delivering exact probabilities in milliseconds instead of relying on stochastic sampling.

---

## Performance Benchmark: Monte Carlo vs Markov Chains

The shift from empirical stochastic simulation (**Monte Carlo**) to analytical resolution (**Markov Chains**) led to an enormous performance leap, replacing random number generation and repeated dice rolling with exact, memoized state evaluations:

| Engine / Method | Simulations per Battle | Execution Time | Speedup | Performance Improvement |
| :--- | :--- | :--- | :--- | :--- |
| **Markov Chains (v1.2)** | *Exact analytical calculation* | **19 ms** | **Baseline (Exact)** | **Exact Ground Truth** |
| Monte Carlo (v1.0) | 10,000 | 783 ms | ~41.2x slower | **+4,021.05% faster** |
| Monte Carlo (v1.0) | 100,000 | 7,699 ms | ~405.2x slower | **+40,421.05% faster** |
| Monte Carlo (v1.0) | 1,000,000 | 84,639 ms (~1.4 min) | ~4,454.7x slower | **+445,368.42% faster** |

> [!Tip]
> While Monte Carlo requires exponentially more iterations and CPU time to converge towards true probabilities, the **Markov Chain model calculates the exact mathematical probability in just 19 ms**, eliminating variance and making real-time analysis instant.

---

## Project Structure

```
RiskEngine/
├── Core/                         # Main engine source code
│   ├── include/                  # Header files (.hpp)
│   │   ├── Engine.hpp            # Orchestration: evaluates and ranks attacks
│   │   ├── Board.hpp             # Board representation and adjacency graph
│   │   ├── GameState.hpp         # Game state management and attack enumeration
│   │   └── RiskProbability.hpp   # Exact battle probability via Markov chains
│   ├── src/                      # Implementation files (.cpp)
│   │   ├── Engine.cpp
│   │   ├── Board.cpp
│   │   ├── GameState.cpp
│   │   └── RiskProbability.cpp
│   ├── Assets/                   # Game data files & diagrams
│   │   ├── Board.txt             # Territory adjacency data
│   │   ├── dataGame.txt          # Player/territory state
│   │   └── LogoReadme.png
│   ├── bin/                      # Compiled binaries
│   │   └── risk_engine
│   └── main.cpp                  # Entry point
├── Training/                     # Incremental learning & archive projects
│   ├── Step1/                    # Dice rolling basics
│   ├── Step2/                    # Army representation
│   ├── Step3/                    # Battle simulation
│   ├── Step4/                    # Monte Carlo prototype
│   └── Step5_Montecarlo/         # Full Monte Carlo engine archive (v1.0)
```

---

## How It Works

1. **Board & State Loading:**
   [`Board`](Core/include/Board.hpp) loads territory adjacencies from `Board.txt`, and [`GameState`](Core/include/GameState.hpp) loads current ownership and troop counts from `dataGame.txt`.
2. **Attack Enumeration:**
   [`GameState::getPossibleAttacks`](Core/include/GameState.hpp) finds all legal attacks `(from, to)` for the selected player where the player owns `from` and an opponent controls adjacent `to`.
3. **Exact Probability Calculation:**
   For each attack, [`Engine`](Core/include/Engine.hpp) calls [`RiskProbability`](Core/include/RiskProbability.hpp). Using precomputed transition probability matrices for Risk combat (attacker rolling up to 3 dice, defender rolling up to 2 dice) and recursive state transitions with memoization, it computes the exact win probability in $O(A \times D)$ time.
4. **Ranking & Display:**
   [`Engine`](Core/include/Engine.hpp) sorts all viable attacks in descending order of success rate and outputs the recommended moves and total execution time.

---

## Core Components

| Component | Purpose |
| :--- | :--- |
| **[`Engine`](Core/include/Engine.hpp)** | Orchestrates attack evaluation, benchmarks run time, and ranks moves |
| **[`RiskProbability`](Core/include/RiskProbability.hpp)** | Computes exact battle win probability using absorbing Markov chains |
| **[`GameState`](Core/include/GameState.hpp)** | Manages territory ownership, tank counts, and legal attack paths |
| **[`Board`](Core/include/Board.hpp)** | Parses and represents territory adjacency graph from `Board.txt` |

*(Note: The previous simulation pipeline consisting of `MonteCarlo`, `Battle`, `Dice`, and `Army` has been archived under [`Training/Step5_Montecarlo/`](Training/Step5_Montecarlo/).)*

---

## READ CAREFULLY
This project was created for educational purposes. It currently uses data loaded from `.txt` files.
The engine uses standard international rules (attacker rolls up to 3 dice, defender up to 2 dice, defender wins ties).

A planned Python computer vision module will allow extracting the game state directly from a photograph of a physical board.

---

## Building & Usage

### Prerequisites
- C++17 compatible compiler (`g++` recommended)
- Linux / Unix environment

### Compilation
```bash
cd Core
g++ -std=c++17 main.cpp src/*.cpp -o bin/risk_engine -I./include
```

### Running
```bash
./bin/risk_engine <player>
```

---

## Roadmap

- [x] **v1.0** — Monte Carlo simulation engine (dice-based stochastic simulation, archived in `Training/Step5_Montecarlo`)
- [x] **v1.2** — Markov Chain exact probability solver (analytical resolution with memoization, sub-millisecond evaluation)
- [ ] **v1.3** — Dynamic player and parameter selection from CLI
- [ ] **v2.0** — Computer Vision (Python / OpenCV) to extract game state directly from a photo of the board
- [ ] **v3.0** — Goal-oriented AI: multi-turn path planning and move suggestions aligned with secret mission cards

---

## Why C++

Evaluating game state combinations and traversing territory graphs demands minimal overhead. Transitioning from Monte Carlo to Markov Chains reduced evaluation times from tens of seconds to just 19 milliseconds, making real-time analysis instant and predictable.

---

## License

MIT License
