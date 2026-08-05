# RiskEngine
<div align="center">
  <img width="400" height="400" alt="LogoReadme" src="https://github.com/user-attachments/assets/0ff1680b-b6b3-42cd-b889-08ad6cec721d" />
</div>
A probabilistic engine for the board game Risk, built to estimate win probabilities and suggest optimal moves through large-scale simulation.

Given full board state — players, territories, tanks per territory, assigned objectives, and enemy troop movements — the engine runs thousands of simulations using the **Monte Carlo method** to estimate each player's probability of winning.

> **Status**: early development. The core engine is not yet implemented. See [Roadmap](#roadmap) below.

---

## Project Structure

The `training/` folder contains smaller, self-contained projects built incrementally as stepping stones toward the full engine. Each one is documented separately.

The `Core/` folder contains all the files required for the engine to run. Check the compilation instructions if you have any questions.

---

## Roadmap

- [x] **Battle simulator** — Monte Carlo resolver for single Risk battles (attacker vs defender), see `training/battle-simulator`
- [x] **Board representation** — graph-based model of territories, adjacency, and ownership
- [ ] **Full game state simulator** — multi-territory, multi-player turn simulation
- [ ] **Move suggestion engine** — evaluate candidate moves by simulated win-rate impact
- [ ] **Board input via image recognition** (Python/CV) — extract game state from a photo of the physical board

---

## Why C++

Simulating thousands of full game states requires raw performance. The core engine is written in C++; a separate Python component (planned) will handle board-state extraction from images.

---

## License

MIT
