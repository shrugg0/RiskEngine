# RiskEngine - Simulatore di Battaglie Stile Risk

Un motore di simulazione di battaglie ispirato al famoso gioco di strategia **Risk**, sviluppato in C++ per esercitarsi con concetti di Programmazione Orientata a Oggetti, STL e logica di gioco.

## Struttura del Progetto

```
RiskEngine/
├── include/           # File header (dichiarazioni delle classi)
│   ├── Army.hpp       # Dichiarazione classe Army
│   ├── Battle.hpp     # Dichiarazione classe Battle
│   └── Dadi.hpp       # Dichiarazione classe Dadi
├── src/              # File source (implementazioni)
│   ├── Army.cpp       # Implementazione classe Army
│   ├── Battle.cpp     # Implementazione classe Battle
│   └── Dadi.cpp       # Implementazione classe Dadi
├── main.cpp          # Punto di ingresso del programma
└── main              # Eseguibile compilato
```

## Classi Principale

### Army (`Army.hpp` / `Army.cpp`)
Rappresenta un esercito con le seguenti proprietà:
- **player**: nome del giocatore
- **tanks**: numero di unità operative
- **territori**: vettore di territori controllati

**Metodi principali:**
- `getPlayer()`, `getTanks()`, `getNumberTerritori()` - Getter
- `updateTanks(int)` - Aggiorna il numero di unità
- `updateTerritori(string)` - Aggiunge un territorio

### Battle (`Battle.hpp` / `Battle.cpp`)
Gestisce la logica di battaglia tra due eserciti.
- **Simulazione**: Tira i dadi per entrambi gli eserciti
- **Confronto**: I valori vengono ordinati in ordine decrescente e confrontati
- **Vincitore**: L'esercito con più unità sopravvissute vince il confronto

### Dadi (`Dadi.hpp` / `Dadi.cpp`)
Gestisce il lancio dei dadi a casa con:
- **faces**: numero di facce del dado (default: 6)
- **multiply**: quantità di dadi da tirare
- **Tira()**: genera numeri casuali distribuiti uniformemente

## Meccanica di Gioco (Ispirata a Risk)

1. **Lancio Dadi**: Ogni esercito tira un numero configurabile di dadi
2. **Ordinamento**: I risultati vengono ordinati in ordine decrescente
3. **Confronto**: I valori vengono confrontati coppia per coppia (massimo 3 confronti per round)
4. **Perdite**: 
   - Se il valore dell'attaccante è **maggiore** del difensore → vince l'attaccante
   - Se il valore del difensore è **maggiore o uguale** → vince il difensore
5. **Risultato**: Vengono aggiornate le unità perse e si determina il vincitore del round

## Compilazione

```bash
# Compilazione con g++
g++ -std=c++17 -o main main.cpp src/Army.cpp src/Battle.cpp src/Dadi.cpp

# Esecuzione
./main
```

## Esempio di Uso

```cpp
Army esercito1("Nero", 30, 0);   // 30 unità per giocatore Nero
Army esercito2("Rosso", 20, 0);  // 20 unità per giocatore Rosso

Battle battle(esercito1, esercito2);
std::string winner = battle.simulaRound();
// Output: messaggi con i risultati dei dadi e le perdite
```

## Note Tecniche

- **Librerie utilizzate**: `<iostream>`, `<vector>`, `<algorithm>`, `<random>`
- **Pattern utilizzati**: Programmazione Orientata a Oggetti, incapsulamento
- **Random**: Utilizza `std::random_device` e `std::mt19937` per generazione casuale

## Possibili Miglioramenti

1. Aggiungere log di battaglie multiple
2. Implementare verifica delle condizioni di vittoria
3. Aggiungere interfaccia utente
4. Espandere la gestione dei territori e delle conquiste