#ifndef ARMY_HPP
#define ARMY_HPP

#include <vector>
#include <string>

class Army
{
private:
    std::string player;
    int tanks;
    int territoriesCount;
    std::vector<std::string> territories;

public:
    Army(std::string player, int tanks);

    // Getters
    std::string getPlayer();

    int getTanks();

    void updateTanks(int toAdd);
};
#endif
