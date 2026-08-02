#include <iostream>
#include <vector>

#include "Army.hpp"


Army::Army(std::string player, int tanks, int territori) : player(player), tanks(tanks), NumberTerritori(territori) {}

std::string Army::getPlayer()
{
    return this->player;
}

int Army::getTanks()
{
    return this->tanks;
}

int Army::getNumberTerritori()
{
    return this->NumberTerritori;
}

void Army::updateTanks(int toAdd)
{
    this->tanks += toAdd;
}

void Army::updateTerritori(std::string toAdd)
{
    this->territori.push_back(toAdd);
}

void Army::listTerritori()
{
    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "Territori posseduti dal giocatore " << Army::getPlayer() << ":" << std::endl;
    for(std::string territorio : this->territori){
        std::cout << territorio << " ";
    }
    std::cout << "\n------------------------------------------------------------\n";
}
