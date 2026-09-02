#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <string>

#include "Army.hpp"
#include "Dice.hpp"

class Battle
{
private:
    Army attackerArmy;
    Army defenderArmy;
    Dice attackerDice;
    Dice defenderDice;
    int diceCap = 3;
    bool verbose;
public:
    Battle(Army att, Army dif, bool verbose);

    std::string simulateRound();

    int getAttackerTanks();

    int getDefenderTanks();

    void setDiceCap();
};
#endif
