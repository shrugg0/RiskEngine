#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/Dice.hpp"


Battle::Battle(Army att, Army dif, bool verbose) : attackerArmy(att), defenderArmy(dif), attackerDice(6,3), defenderDice(6,3), diceCap(2), verbose(verbose) {};

std::string Battle::simulateRound()
{
    std::string winner;
    // Dice count management, recalculated every round based on available tanks
    int diceAtk = std::min(3, attackerArmy.getTanks() - 1);
    int diceDif = std::min(diceCap, defenderArmy.getTanks());

    attackerDice.setDiceCount(diceAtk);
    defenderDice.setDiceCount(diceDif);
    int attackerLosses = 0, defenderLosses = 0;

    std::vector attackerRolls = attackerDice.roll();
    std::vector defenderRolls = defenderDice.roll();


    // Sort vectors in descending order
    std::sort(attackerRolls.begin(), attackerRolls.end(), [](int a, int b) { return a > b; });
    std::sort(defenderRolls.begin(), defenderRolls.end(), [](int a, int b) { return a > b; });




    for (size_t i = 0; i < std::min(attackerRolls.size(), defenderRolls.size()); i++)
    {
        if (attackerRolls[i] <= defenderRolls[i])
        {
            attackerLosses++;
        }else{
            defenderLosses++;
        }
    }
    attackerArmy.updateTanks(-attackerLosses);
    defenderArmy.updateTanks(-defenderLosses);

    if(verbose)
    {
        std::cout << "Attacker:" << std::endl;
        for (int n : attackerRolls)
        {
            std::cout << n << " ";
        }
        std::cout << "\nDefender:" << std::endl;
        for (int n : defenderRolls)
        {
            std::cout << n << " ";
        }

        std::cout << "\nLosses attacker's side: " << attackerLosses << std::endl;
        std::cout << "Losses defender's side: " << defenderLosses << std::endl;

        std::cout << "Tanks left on the attacker's territory :" << attackerArmy.getTanks() << std::endl;
        std::cout << "Tanks left on the defender's territory :" << defenderArmy.getTanks() << std::endl;
    }




    if (attackerLosses > defenderLosses)
    {
        winner = defenderArmy.getPlayer();
    }else if (attackerLosses < defenderLosses){
        winner = attackerArmy.getPlayer();
    }else{
        winner = "Tie";
    }
    return winner;
}
void Battle::setDiceCap()
{
    int newCap;
    do
    {
        std::cout << "\nNew dice cap ( 2 or 3 ): ";
        std::cin >> newCap;
    } while (newCap != 2 && newCap != 3);

    this->diceCap = newCap;
}

int Battle::getAttackerTanks() const
{
    return attackerArmy.getTanks();
}

int Battle::getDefenderTanks() const
{
    return defenderArmy.getTanks();
}
