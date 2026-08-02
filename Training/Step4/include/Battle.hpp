#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Army.hpp"
#include "Dadi.hpp"

class Battle
{
private:
    Army esercito1;
    Army esercito2;
    Dadi dadoAtk;
    Dadi dadoDif;
public:
    Battle(Army att, Army dif);

    std::string simulaRound();

    int getAtkTanks();

    int getDifTanks();
};
