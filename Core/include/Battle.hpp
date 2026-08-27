#ifndef BATTLE_HPP
#define BATTLE_HPP



#include "Army.hpp"
#include "Dadi.hpp"

class Battle
{
private:
    Army esercito1;
    Army esercito2;
    Dadi dadoAtk;
    Dadi dadoDif;
    int diceCap = 3;
public:
    Battle(Army att, Army dif);

    std::string simulaRound();

    int getAtkTanks();

    int getDifTanks();

    void setDiceCap();
};
#endif
