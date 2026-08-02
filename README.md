# risiko-engine

A probabilistic engine for the board game Risk, built to estimate win probabilities and suggest optimal moves through large-scale simulation.

Given full board state — players, territories, tanks per territory, assigned objectives, and enemy troop movements — the engine runs thousands of simulations using the **Monte Carlo method** to estimate each player's probability of winning.

> ⚠️ **Status**: early development. The core engine is not yet implemented. See [Roadmap](#roadmap) below.

---

## Project Structure

risiko-engine/
├── training/ # Learning modules, built while developing C++ OOP skills
│ └── battle-simulator/ # Standalone Monte Carlo battle resolver (see its own README)
└── (core engine — coming soon)


The `training/` folder contains smaller, self-contained projects built incrementally as stepping stones toward the full engine. Each one is documented separately.

---

## Roadmap

- [x] **Battle simulator** — Monte Carlo resolver for single Risk battles (attacker vs defender), see `training/battle-simulator`
- [ ] **Board representation** — graph-based model of territories, adjacency, and ownership
- [ ] **Full game state simulator** — multi-territory, multi-player turn simulation
- [ ] **Move suggestion engine** — evaluate candidate moves by simulated win-rate impact
- [ ] **Board input via image recognition** (Python/CV) — extract game state from a photo of the physical board

---

## Why C++

Simulating thousands of full game states requires raw performance. The core engine is written in C++; a separate Python component (planned) will handle board-state extraction from images.

---

## License

MIT
