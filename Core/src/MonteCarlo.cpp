#include <iostream>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/MonteCarlo.hpp"


MonteCarlo::MonteCarlo(Army atk, Army dif, int n, bool verbose) : attackerArmy(atk), defenderArmy(dif), simulations(n), verbose(verbose) {};

std::string MonteCarlo::simulateBattle()
{
    int i = 1;
    Army atkCopy = attackerArmy;
    Army difCopy = defenderArmy;

    Battle battle(atkCopy, difCopy, verbose);

    //battle.setDiceCap();

    while ((battle.getAttackerTanks() - 1) > 0 && battle.getDefenderTanks() > 0)
    {
        if (verbose) {
            std::cout << "\n============== Start round N " << i << "==============" << std::endl;
        }
        std::string winnerRound = battle.simulateRound();
        i++;
    }
    std::string winner;
    if (battle.getDefenderTanks() == 0)
    {
        winner = attackerArmy.getPlayer();
    }else{
        winner = defenderArmy.getPlayer();
    }

    return winner;
}

void MonteCarlo::runSimulations()
{
    for (size_t i = 1; i <= simulations; i++)
    {
        if (verbose) {
            std::cout << "\n============== Start simulation N " << i << "==============" << std::endl;
        }
        std::string winnerGame = MonteCarlo::simulateBattle();
        stats[winnerGame]++;
    }

}

void MonteCarlo::printStats()
{
    std::cout << "Results of " << simulations << " simulations:" << std::endl;

    int totalWins = stats[attackerArmy.getPlayer()] + stats[defenderArmy.getPlayer()] + stats["Tie"];
    float sumPercent = 0.0f;

    std::cout << "  - " << attackerArmy.getPlayer() << " (attacker): "
              << stats[attackerArmy.getPlayer()] << " wins ("
              << ((float)stats[attackerArmy.getPlayer()] / simulations) * 100 << "%)" << std::endl;

    std::cout << "  - " << defenderArmy.getPlayer() << " (defender): "
              << stats[defenderArmy.getPlayer()] << " wins ("
              << ((float)stats[defenderArmy.getPlayer()] / simulations) * 100 << "%)" << std::endl;

    float percentTie = ((float)stats["Tie"] / simulations) * 100;
    std::cout << "  - Tie: " << stats["Tie"] << " times ("
              << percentTie << "%)" << std::endl;

    sumPercent = ((float)stats[attackerArmy.getPlayer()] / simulations) * 100 +
                  ((float)stats[defenderArmy.getPlayer()] / simulations) * 100 +
                  percentTie;
    std::cout << "\nTotal recorded simulations: " << totalWins << std::endl;
    std::cout << "Sum of percentages: " << sumPercent << "%" << std::endl;
}

double MonteCarlo::getWinRate()
{
    return ((double)stats[attackerArmy.getPlayer()] / simulations) * 100;
}
