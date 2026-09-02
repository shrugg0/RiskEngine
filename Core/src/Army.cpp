#include "../include/Army.hpp"
#include <string>


Army::Army(std::string player, int tanks) : player(player), tanks(tanks) {}

std::string Army::getPlayer() const
{
    return this->player;
}

int Army::getTanks() const
{
    return this->tanks;
}

void Army::updateTanks(int toAdd)
{
    this->tanks += toAdd;
}
