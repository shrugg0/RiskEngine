#include <iostream>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/MonteCarlo.hpp"


MonteCarlo::MonteCarlo(Army atk, Army dif, int n, bool verbose) : esercito1(atk), esercito2(dif), sims(n), verbose(verbose) {};

std::string MonteCarlo::SimulaBattle()
{
    int i = 1;
    Army atkCopy = esercito1;
    Army difCopy = esercito2;

    Battle battle(atkCopy, difCopy, verbose);

    //battle.setDiceCap();

    while ((battle.getAtkTanks() -1) > 0 && battle.getDifTanks() > 0)
    {
        if (verbose) {
            std::cout << "\n============== Start round N " << i << "==============" << std::endl;
        }
        std::string winnerRound = battle.simulaRound();
        i++;
    }
    std::string winner;
    if (battle.getDifTanks() == 0)
    {
        winner = esercito1.getPlayer();
    }else{
        winner = esercito2.getPlayer();
    }

    return winner;
}

void MonteCarlo::RunnaSimulazioni()
{
    for (size_t i = 1; i <= sims; i++)
    {
        if (verbose) {
            std::cout << "\n============== Start simulation N " << i << "==============" << std::endl;
        }
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
}

double MonteCarlo::getWinRate()
{
    return ((double)stats[esercito1.getPlayer()] / sims) * 100;
}
