#pragma once

#include <iostream>
#include <vector>


class Army
{
private:
    std::string player;
    int tanks;
    int NumberTerritori;
    std::vector<std::string> territori;

public:
    Army(std::string player, int tanks, int territori);

    // Getters
    std::string getPlayer();

    int getTanks();

    int getNumberTerritori();

    void updateTanks(int toAdd);

    void updateTerritori(std::string toAdd);

    void listTerritori();
    
};



