#include <iostream>
#include <vector>
#include <algorithm>

#include "include/Army.hpp"
#include "include/Battle.hpp"
#include "include/Dadi.hpp"
#include "include/MonteCarlo.hpp"

int main(void){
    int blackTanks, redTanks;
    std::cout << "Carri armati per il giocatore Nero: ";
    std::cin >> blackTanks;
    std::cout << "\nCarri armati per il giocatore Rosso: ";
    std::cin >> redTanks;
    
    Army esercito1("Nero", blackTanks, 0);
    Army esercito2("Rosso", redTanks, 0);

    int volte;
    std::cout << "Numero di simulazioni da svolgere: ";
    std::cin >> volte;

    MonteCarlo simulatore(esercito1, esercito2, volte);
    simulatore.RunnaSimulazioni();
    simulatore.PrintStats();
    
    
}