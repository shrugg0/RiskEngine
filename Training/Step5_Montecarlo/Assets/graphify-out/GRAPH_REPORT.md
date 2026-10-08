# Graph Report - Core  (2026-09-22)

## Corpus Check
- 26 files · ~104,724 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 1 file(s) not represented in the graph (top: (none) 1)

## Summary
- 229 nodes · 339 edges · 13 communities (12 shown, 1 thin omitted)
- Extraction: 96% EXTRACTED · 4% INFERRED · 0% AMBIGUOUS · INFERRED: 15 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- Board Data and File I/O
- Markov Chain Probability Engine
- Monte Carlo and Army Domain
- Architecture Layers and Design Schema
- Attack Combat Entities and Game State
- Probability Computation and Entry Points
- Battle Dice and Random Systems
- System Architecture Diagram
- Risk Game Territory Geography
- Board Loading and Parsing
- Project Logo and Branding
- Combat Probability Analysis
- Board Map Document

## God Nodes (most connected - your core abstractions)
1. `GameState` - 17 edges
2. `Board` - 16 edges
3. `Army` - 15 edges
4. `Battle` - 15 edges
5. `MonteCarlo` - 15 edges
6. `Engine` - 12 edges
7. `RiskProbability` - 10 edges
8. `Dice` - 10 edges
9. `Territory Adjacency Graph` - 9 edges
10. `Attack` - 8 edges

## Surprising Connections (you probably didn't know these)
- `Data and Topology Layer` --conceptually_related_to--> `Board`  [EXTRACTED]
  Assets/architecture_schema.svg → include/Board.hpp
- `Territory Position Indices` --semantically_similar_to--> `Territory Adjacency Graph`  [INFERRED] [semantically similar]
  Assets/Risk_game_board..png → Assets/Board.txt
- `Data Structures and Entities Layer` --conceptually_related_to--> `Army`  [EXTRACTED]
  Assets/architecture_schema.svg → include/Army.hpp
- `Engine and Monte Carlo Orchestration Layer` --conceptually_related_to--> `Engine`  [EXTRACTED]
  Assets/architecture_schema.svg → include/Engine.hpp
- `Engine and Monte Carlo Orchestration Layer` --conceptually_related_to--> `GameState`  [EXTRACTED]
  Assets/architecture_schema.svg → include/GameState.hpp

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Risk Board Game State Data** — assets_board_territory_adjacency, assets_datagame_territory_state, assets_makarovchain_readme_markov_chain_validation [INFERRED 0.85]
- **RiskEngine Brand Identity Symbols** — assets_logoreadme_monte_carlo_casino, assets_logoreadme_stochastic_dice, assets_logoreadme_financial_chart [INFERRED 0.85]
- **Risk Battle Odds System** — assets_prob_win_probability_matrix, assets_prob_attacker_advantage_scaling, assets_prob_dice_combat_odds [INFERRED 0.85]
- **Monte Carlo Attack Simulation Pipeline** — include_engine_engine, include_montecarlo_montecarlo, include_battle_battle, include_army_army, include_dice_dice [EXTRACTED 1.00]
- **Board State and Topology Attack Discovery Flow** — include_board_board, include_gamestate_gamestate, include_engine_engine [EXTRACTED 1.00]
- **End-to-End Orchestration Lifecycle** — main_main, include_board_board, include_gamestate_gamestate, include_engine_engine, include_montecarlo_montecarlo [EXTRACTED 1.00]
- **Production Simulation Pipeline** — assets_diagram_executable_entry, assets_diagram_engine_orchestrator, assets_diagram_montecarlo_evaluator, assets_diagram_battle_resolver, assets_diagram_dadi_dice_rules [EXTRACTED 1.00]
- **Domain State Initialization Subsystem** — assets_diagram_datagame_txt, assets_diagram_board_txt, assets_diagram_board_model, assets_diagram_gamestate_model, assets_diagram_army_domain_state [EXTRACTED 1.00]
- **Alternative Algorithms and Educational Prototypes** — assets_diagram_makarovchain_prototype, assets_diagram_riskprobability_algorithm, assets_diagram_training_step4_executable [EXTRACTED 1.00]

## Communities (13 total, 1 thin omitted)

### Community 0 - "Board Data and File I/O"
Cohesion: 0.07
Nodes (31): Assets/Board.txt Graph File, Assets/dataGame.txt Match State File, Board, adjList, boardData, fileName, getNeighbors, loadData (+23 more)

### Community 1 - "Markov Chain Probability Engine"
Cohesion: 0.13
Nodes (17): map, vector, cctype, cstring, fstream, string, Army::Army(), Army::getPlayer() (+9 more)

### Community 2 - "Monte Carlo and Army Domain"
Cohesion: 0.07
Nodes (27): Monte Carlo Attack Evaluation Workflow, Army, getPlayer, getTanks, player, tanks, territories, territoriesCount (+19 more)

### Community 3 - "Architecture Layers and Design Schema"
Cohesion: 0.09
Nodes (25): Battle and Combat Logic Layer, Risk Combat Resolution Rules, Data and Topology Layer, RiskEngine Architecture and Object Interaction Schema, Engine and Monte Carlo Orchestration Layer, updateTanks, Battle, attackerArmy (+17 more)

### Community 4 - "Attack Combat Entities and Game State"
Cohesion: 0.10
Nodes (25): Data Structures and Entities Layer, AttackStats, attack, winProbability, Attack, from, to, GameState (+17 more)

### Community 5 - "Probability Computation and Entry Points"
Cohesion: 0.14
Nodes (14): algorithm, main(), RiskProbability, computed, memo, solve, transitions, winProbability (+6 more)

### Community 6 - "Battle Dice and Random Systems"
Cohesion: 0.13
Nodes (6): array, chrono, random, Battle::simulateRound(), string, Dice::roll()

### Community 7 - "System Architecture Diagram"
Cohesion: 0.17
Nodes (17): RiskEngine System Architecture Diagram, Army domain state [Army.cpp], Battle combat resolver [Battle.cpp], Board topology model [Board.cpp], Board topology text asset [Board.txt], Dadi dice rules [Dadi.cpp], Game snapshot text asset [dataGame.txt], Engine orchestrator [Engine.cpp] (+9 more)

### Community 8 - "Risk Game Territory Geography"
Cohesion: 0.13
Nodes (16): Africa Continent, Asia Continent, Australia Continent, Europe Continent, North America Continent, South America Continent, Territory Adjacency Graph, Player Color Assignment (+8 more)

### Community 9 - "Board Loading and Parsing"
Cohesion: 0.27
Nodes (7): Board::Board(), Board::getNeighbors(), Board::printNeighbors(), Board::trim(), string, vector, sstream

### Community 10 - "Project Logo and Branding"
Cohesion: 0.67
Nodes (4): Financial Chart and Market Trend Indicator, RiskEngine Logo, Monte Carlo Casino Motif, Stochastic Dice Representation

### Community 11 - "Combat Probability Analysis"
Cohesion: 1.00
Nodes (3): Attacker Advantage Scaling with Unit Count, Risk Dice Combat Odds, Risk Battle Win Probability Matrix

## Knowledge Gaps
- **70 isolated node(s):** `attackerLoss`, `defenderLoss`, `probability`, `memo`, `computed` (+65 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 111 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **1 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Army` connect `Monte Carlo and Army Domain` to `Markov Chain Probability Engine`, `Architecture Layers and Design Schema`, `Attack Combat Entities and Game State`?**
  _High betweenness centrality (0.121) - this node is a cross-community bridge._
- **Why does `Battle` connect `Architecture Layers and Design Schema` to `Monte Carlo and Army Domain`, `Battle Dice and Random Systems`?**
  _High betweenness centrality (0.095) - this node is a cross-community bridge._
- **Why does `Board` connect `Board Data and File I/O` to `Markov Chain Probability Engine`, `Architecture Layers and Design Schema`, `Attack Combat Entities and Game State`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **What connects `attackerLoss`, `defenderLoss`, `probability` to the rest of the system?**
  _70 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Board Data and File I/O` be split into smaller, more focused modules?**
  _Cohesion score 0.06881720430107527 - nodes in this community are weakly interconnected._
- **Should `Markov Chain Probability Engine` be split into smaller, more focused modules?**
  _Cohesion score 0.12688172043010754 - nodes in this community are weakly interconnected._
- **Should `Monte Carlo and Army Domain` be split into smaller, more focused modules?**
  _Cohesion score 0.07126436781609195 - nodes in this community are weakly interconnected._