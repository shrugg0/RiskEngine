#ifndef ARMY_HPP
#define ARMY_HPP

#include <vector>
#include <string>

class Army
{
private:
    std::string player;
    int tanks;
    int NumberTerritori;
    std::vector<std::string> territori;

public:
    Army(std::string player, int tanks);

    // Getters
    std::string getPlayer();

    int getTanks();

    void updateTanks(int toAdd);
};
#endif
