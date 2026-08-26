# Dev Notes — RiskEngine

Riferimento tecnico per riprendere lo sviluppo su `Core/`. Ignora l'obiettivo del progetto; qui si guarda **come funziona il codice così com'è adesso**.

---

## Build & run

```bash
cd Core
g++ -std=c++17 main.cpp src/*.cpp -o risk_engine -I./include
./risk_engine     # chiede: numero di simulazioni per battaglia (10000 consigliate)
```

Niente dipendenze esterne. Il binario finisce in `Core/`, non in `build/`.

> ⚠️ `Dadi::Tira()` stampa i dadi a schermo? No. `MonteCarlo::SimulaBattle()` e `Battle::simulaRound()` stampano ogni round a stdout — con tante simulazioni è lentissimo (c'è un `usleep(10ms)` per round). Se vuoi profilarvi togli le stampe o redirect su /dev/null.

---

## Pipeline di esecuzione (pensala come data flow)

```
main.cpp
  → Board("Assets/Board.txt").loadData()          // parsed in adjList (map<string, vector<string>>)
  → GameState("Assets/dataGame.txt").loadData()    // parsed in info (map<string, TerritoryState>)
  → Engine en; en.EvaluateAllAttacks("Red", gs, board, nSim);
  → en.PrintResult();                              // stampa attacchi ordinati per probab. vittoria discendente
```

`Board` e `GameState` **aprono il file nel costruttore** e lo tengono aperto (memorizzato come membro `std::ifstream`). `loadData()` legge ciò che c'è nel buffer. Se chiami `loadData()` due volte il file è già consumato → niente succede. Da tenere a mente per debugging.

---

## Classi principali

### Army (Engine.hpp / Army.cpp)
- **Cosa è:** value type minimale. `(player string, tanks int)`.
- **Costruttore:** `Army(string player, int tanks)`.
- **Metodi chiave:** `getPlayer()`, `getTanks()`, `updateTanks(int toAdd)` — += toAdd, accetta valori negativi.
- **Nota:** è copiato per valore in `Battle` e `MonteCarlo`, quindi le modifiche durante una simulazione **non** toccano `GameState`. Il stato persisterà invariato tra un attacco e l'altro.

### Dadi (Dadi.hpp / Dadi.cpp)
- **Cosa fa:** genera N dadi a F facce.
- **Costruttori:** `Dadi()` (6 facce, 1 dado), `Dadi(faces)`, `Dadi(faces, multiply)`.
- **Metodo chiave:** `Tira()` → `vector<int>`.
- **RNG:** `static std::random_device rd; static std::mt19937 gen(steady_clock...)`. Il generatore è **static** → condiviso da tutti gli oggetti `Dadi`. `std::uniform_int_distribution<int>(1, faces)` ricreato ad ogni chiamata (non `static`, ma è ok: è cheap).
- **Setter:** `setFaces()`, `setMultiply()` — usati in `Battle::simulaRound()` per impostare il numero di dadi dinamicamente.

### Battle (Battle.hpp / Battle.cpp)
- **Cosa fa:** simula **un singolo round** di combattimento (non l'intera battaglia).
- **Costruttore:** `Battle(Army att, Army dif)` — copia per valore entrambi gli eserciti. Inizializza `dadoAtk(6,3)`, `dadoDif(6,3)`, `diceCap=2`.
- **Metodo chiave:** `simulaRound()` → `string` (nome del vincitore del round).
  - Calcola `diceAtk = min(3, atk.tanks - 1)`, `diceDif = min(diceCap, dif.tanks)`.
  - Imposta i moltiplicatori sui due `Dadi`, tira, ordina discendente.
  - Confronta coppia per coppia: `atk[i] <= dif[i]` → atk perde 1, altrimenti dif perde 1.
  - Aggiorna i serbatoi via `updateTanks(-losses)`.
  - Ritorna il vincitore del round (o `"Tie"`).
- **Metodi di accesso:** `getAtkTanks()`, `getDifTanks()`.
- **Setter:** `setDiceCap()` — legge interattivamente 2 o 3 da stdin (commentato in MonteCarlo).

### MonteCarlo (MonteCarlo.hpp / MonteCarlo.cpp)
- **Cosa fa:** esegue N simulazioni complete di battaglia e raccoglie le vittorie.
- **Costruttore:** `MonteCarlo(Army atk, Army dif, int n)` — salva `startTime` (chrono).
- **Metodi chiave:**
  - `SimulaBattle()` → `string` (nome del vincitore della battaglia intera). Loop: `while ((atk -1) > 0 && dif > 0)` chiama `simulaRound()`.
  - `RunnaSimulazioni()` → ciclo `for i in [1..sims]` che chiama `SimulaBattle()`, accumula in `stats[string]`.
  - `getWinRate()` → `((double)stats[atk.player] / sims) * 100` — è la percentuale di vittorie dell'**attaccante**.
  - `PrintStats()` → stampa tabellina con vittorie, pareggi, somma %, tempo.
- **Nota debug:** `SimulaBattle()` stampa `"============== Start round N x ==============="` ad ogni round, e `RunnaSimulazioni()` stampa `"============== Start simulation N x ==============="`. È questo che rompe le palle con output volume.

### GameState (GameState.hpp / GameState.cpp)
- **Cosa fa:** tiene traccia di chi possiede ogni territorio e quanti carri ci sono.
- **Dati:** `info` = `map<string, TerritoryState>` dove `TerritoryState { owner; tanks }`.
- **Costruttore:** `GameState(filename)` — apre `dataGame.txt`, salva `fileName`.
- **Metodi chiave:**
  - `getOwner(territory)` → string. Lancia eccezione se non in mappa.
  - `getTanks(territory)` → int.
  - `getListTerrOfPlayer(player)` → vector<string> di territi del giocatore.
  - `getPossibleAttacks(player, board)` → vector<Attack>. Per ogni territorio del giocatore, guarda i vicini su `Board`; se il vicino è di un altro giocatore aggiunge `{from, neighbor}`.
  - `loadData()` → parse di `dataGame.txt`.
- **Formato data:** `"Territory: Owner, tanks"` (es. `Alaska: Red, 5`). Nota lo spazio dopo la virgola? `trim()` lo toglie.
- **Attenzione:** `getTanks()` non controlla se il territorio esiste — ritorna accesso diretto alla mappa, potrebbe default-constructed (owner vuoto, tanks 0). `getOwner()` invece lancia eccezione.

### Board (Board.hpp / Board.cpp)
- **Cosa fa:** grafo di adiacenza dei territori.
- **Dati:** `adjList` = `map<string, vector<string>>`.
- **Costruttore:** `Board(filename)` — apre `Board.txt`.
- **Metodi chiave:**
  - `loadData()` → parse. Ogni riga: `"Territory: vicino1, vicino2, ..."`.
  - `getVicini(state)` → vector<string>. Ritorna `{}` se non trovato.
  - `printBoard()`, `printVicini()`.
- **Formato Board.txt:** niente spazi attorno ai nomi (viene fatto `trim()`), adiacenze separate da virgola.

### Engine (Engine.hpp / Engine.cpp)
- **Cosa fa:** orquestra il tutto — trova gli attacchi, simula, raccoglie risultati.
- **Dati:** `results` = `vector<StatsAttacks>` dove `StatsAttacks { Attack atk; double winProb; }`.
- **Metodi chiave:**
  - `EvaluateAttack(Attack atk, GameState& gs, int nSim)` → `double`. Costruisce due `Army` da `gs.getOwner()/getTanks()`, istanzia un `MonteCarlo`, lo runna, ritorna `mc.getWinRate()`.
  - `EvaluateAllAttacks(giocatore, stato, board, nSim)` → svuota `results`, ottiene `stato.getPossibleAttacks(giocatore, board)`, per ogni attacco chiama `EvaluateAttack` e accoda `{atk, prob}`.
  - `GetResult()` → ritorna il vector.
  - `PrintResult()` → **ordina decrescente per winProb** e stampa: `"Attaccando da X il territorio Y hai il P% di vittoria"`.

---

## Flow di una singola valutazione di attacco

1. `Engine::EvaluateAttack({from="Alaska", to="Northwest Territory"}, gs, 10000)`
2. `Army atk("Red", gs.getTanks("Alaska"))` → `Army("Red", 5)`
3. `Army dif("Blue", gs.getTanks("Northwest Territory"))` → `Army("Blue", 4)`
4. `MonteCarlo mc(atk, dif, 10000)` — copia entrambi gli Army.
5. `mc.RunnaSimulazioni()` → 10000 volte:
   - `SimulaBattle()` → in un loop `Battle b(atkCopy, difCopy)`:
     - `b.simulaRound()` → tira dadi, compari, applica perdite.
     - Loop finché `atk.tanks-1 > 0 && dif.tanks > 0`.
     - Vincitore = chi ha `tanks > 0` all'alt fine.
   - `stats[winner]++`
6. `mc.getWinRate()` = `(stats["Red"] / 10000) * 100` → percentuale vittorie di Red (l'attaccante).

**Il valore che finisce in `StatsAttacks.winProb` è la percentuale di volte in cui l'attaccante (Red) vince l'intera battaglia** (non uno specifico round).

---

## Dati su disco

### Assets/dataGame.txt
Formato: `Territory: Owner, tanks` (uno per riga). Esempio:
```
Alaska: Red, 5
Northwest Territory: Blue, 4
```
Mappa il territorio → chi lo controlla + quanti carri. `GameState::loadData()` parsa con `find(':')` e `find(',')`.

### Assets/Board.txt
Formato: `Territory: vicino1, vicino2, ...` (uno per riga). Grafo non direzionato (se A è vicino di B, B è vicino di A — entrambi devono comparire).

---

## Note di progetto / trappole

- **Player hard-coded:** `main.cpp:20` → `std::string player = "Red";`. Per cambiare chi viene analizzato modifica lì.
- **diceCap (difesa):** valore di default 2 (regola internazionale). `Battle::setDiceCap()` permette 3 ma è commentato in MonteCarlo. Per usarlo de-commenta `battle.setDiceCap();` in `MonteCarlo.cpp:23`, ma richiede input interattivo → non adatto a simulazioni batch.
- **RNG condiviso:** tutti gli oggetti `Dadi` usano lo stesso `static mt19937`. Fine per MonteCarlo ma qualcosa da sapere.
- **Nessun CMakeLists / Makefile:** compilazione manuale con g++.
- **Branch:** lavori su `to-implement`. `Makarov` ha una catena di Markov alternativa (non integrata).
- **Training/:** prototipi educativi (Step1-4). Non sono parte del build di `Core/`. Step4 è una copia standalone della MonteCarlo engine.
- **MakarovChain/:** validatore alternativo, non linkato. `RiskProbability::winProbability(a, d)` usa DP memoizzata.

---

## Per riprendere

1. Decidi dove intervenire (Engine ranking, MonteCarlo RNG, Battle rules, verbosity output).
2. Builda in `Core/`.
3. Se modifichi `Army`/`Battle`/`MonteCarlo`/`Dadi` ricorda che `Engine` li usa tutti in sequenza — controlla costruttori.
4. Se modifichi i formati di `Board.txt` o `dataGame.txt` aggiorna `GameState` e `Board` parsing in pari.
5. Il metodo più probabile da migliorare: togliere le stampe verbose da `SimulaBattle`/`simulaRound` e renderle opzionali (flag), perché a 10000 sims il volume rompe la console.
