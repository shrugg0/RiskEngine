#include <iostream>
#include <vector>

#include "../include/Army.hpp"


Army::Army(std::string player, int tanks, int territori) : player(player), tanks(tanks), NumberTerritori(territori) {}

std::string Army::getPlayer()
{
    return this->player;
}

int Army::getTanks()
{
    return this->tanks;
}

void Army::updateTanks(int toAdd)
{
    this->tanks += toAdd;
}

