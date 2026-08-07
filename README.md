# RiskEngine
<div align="center">
  <img width="400" height="400" alt="LogoReadme" src="https://github.com/user-attachments/assets/0ff1680b-b6b3-42cd-b889-08ad6cec721d" />
</div>

A probabilistic engine for the board game Risk, built to estimate win probabilities and suggest optimal moves through large-scale simulation.

Given full board state — players, territories, tanks per territory, assigned objectives, and enemy troop movements — the engine runs thousands of simulations using the **Monte Carlo method** to estimate each player's probability of winning.

---

## Project Structure

```
RiskEngine/
├── Core/                 # Main engine source code
│   ├── include/         # Header files (.hpp)
│   │   ├── Engine.hpp   # Main engine orchestration
│   │   ├── Board.hpp    # Board representation
│   │   ├── GameState.hpp # Game state management
│   │   ├── Battle.hpp   # Battle simulation logic
│   │   ├── MonteCarlo.hpp # Monte Carlo simulation
│   │   ├── Army.hpp     # Army/troop management
│   │   └── Dadi.hpp     # Dice rolling mechanics
│   ├── src/             # Implementation files (.cpp)
│   ├── Assets/          # Game data files
│   │   ├── Board.txt    # Territory adjacency data
│   │   ├── dataGame.txt # Player/territory state
│   │   └── LogoReadme.png
│   └── main.cpp         # Entry point
├── Training/            # Incremental learning projects
│   ├── Step1/           # Dice rolling basics
│   ├── Step2/           # Army representation
│   ├── Step3/           # Battle simulation
│   └── Step4/           # Full Monte Carlo
└── Core/Assets/MakarovChain/  # Alternative algorithm implementation
```

---

## READ CAREFULLY
This project was created for educational purposes and cannot currently be used in real-world contexts. This is because it uses fictitious, static data saved in a .txt file, and the player being analyzed is hard-coded. The program will be usable once the Python module for image recognition is implemented.

In addition, by default, the program uses the international rules regarding the maximum number of dice that can be used for defense, which is 2. However, it is possible to change this value using a commented-out setter in Montecarlo.cpp, line 23.
---

## Building & Usage

### Prerequisites
- C++ compiler (g++ recommended)
- Linux/Unix environment

### Compilation
```bash
cd Core
g++ -std=c++17 main.cpp src/*.cpp -o risk_engine -I./include
```

### Running
```bash
cd Core
./main
```

The engine loads board and game state from `Board.txt` and `dataGame.txt`, and outputs probability estimates for each territory.

---

## Core Components

| Component | Purpose |
|-----------|---------|
| **Engine** | Orchestrates simulations, evaluates all possible attacks |
| **Board** | Parses territory adjacency from `Board.txt` |
| **GameState** | Manages player armies, territories, objectives |
| **Battle** | Simulates individual dice-based combats |
| **MonteCarlo** | Runs thousands of random simulations |
| **Army** | Territory ownership and troop counts |
| **Dadi** | Risk dice mechanics (attack: 1-3, defend: 1-2) |

---

## Roadmap

- [x] **v1**: Using only the Monte Carlo method for everything
- [ ] **v1.2** — Using Makarov's chain for the probabilistic calculations
- [ ] **v2** — (Python/CV/Computer Vision) — extract game state from a photo of the physical board
- [ ] **v3** — Using the Monte Carlo method based on your gaming objective, suggesting moves that bring you closer to your goal

---

## Why C++

Simulating thousands of full game states requires raw performance. The core engine is written in C++; a separate Python component (planned) will handle board-state extraction from images.

---

## License

MIT License