#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/Dadi.hpp"
#include "../include/MonteCarlo.hpp"
#include "MonteCarlo.hpp"

#define MS 250

MonteCarlo::MonteCarlo(Army atk, Army dif, int n) : esercito1(atk), esercito2(dif), sims(n), startTime(std::chrono::steady_clock::now()) {};

std::string MonteCarlo::SimulaBattle()
{
    int i = 1;
    Army atkCopy = esercito1;
    Army difCopy = esercito2;

    Battle battle(atkCopy, difCopy);

    while ((battle.getAtkTanks() -1) > 0 && battle.getDifTanks() > 0)
    {
        std::cout << "\n============== inizio parita N " << i << "==============" << std::endl;
        std::string winnerRound = battle.simulaRound();
        usleep(MS);
        i++;
    }
    std::string winner;
    if (battle.getAtkTanks() > battle.getDifTanks())
    {
        winner = esercito1.getPlayer();
    }else if (battle.getAtkTanks() < battle.getDifTanks())
    {
        winner = esercito2.getPlayer();
    }else{
        winner = "Pareggio";
    }
    
    return winner;
}

void MonteCarlo::RunnaSimulazioni()
{
    for (size_t i = 1; i <= sims; i++)
    {
        std::cout << "\n============== inizio simulazione N " << i << "==============" << std::endl;
        std::string winnerGame = MonteCarlo::SimulaBattle();
        stats[winnerGame]++;
    }
    
}

void MonteCarlo::PrintStats()
{
    std::cout << "Risultati di " << sims << " simulazioni:" << std::endl;

    int totalWins = stats[esercito1.getPlayer()] + stats[esercito2.getPlayer()] + stats["Pareggio"];
    float sumPercent = 0.0f;

    std::cout << "  - " << esercito1.getPlayer() << " (attaccante): "
              << stats[esercito1.getPlayer()] << " vittorie ("
              << ((float)stats[esercito1.getPlayer()] / sims) * 100 << "%)" << std::endl;

    std::cout << "  - " << esercito2.getPlayer() << " (difensore): "
              << stats[esercito2.getPlayer()] << " vittorie ("
              << ((float)stats[esercito2.getPlayer()] / sims) * 100 << "%)" << std::endl;

    float percentPar = ((float)stats["Pareggio"] / sims) * 100;
    std::cout << "  - Pareggio: " << stats["Pareggio"] << " volte ("
              << percentPar << "%)" << std::endl;

    sumPercent = ((float)stats[esercito1.getPlayer()] / sims) * 100 +
                  ((float)stats[esercito2.getPlayer()] / sims) * 100 +
                  percentPar;
    std::cout << "\nTotale simulazioni registrate: " << totalWins << std::endl;
    std::cout << "Somma percentuali: " << sumPercent << "%" << std::endl;

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "\nTempo totale impiegato: " << duration.count() << " ms" << std::endl;
        
}