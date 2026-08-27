#include "../include/Army.hpp"


Army::Army(std::string player, int tanks) : player(player), tanks(tanks) {}

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
