#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
/* Who controls each territory, and how many tanks, rn ?  */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Board.hpp"

struct TerritoryState {
    std::string owner;
    int tanks;
};
// struct for understand which state i can attack ( to ) from state x
struct Attack{
    std::string from;
    std::string to;
};

class GameState
{
private:
    std::map<std::string, TerritoryState> info;
    std::string fileName;
    std::ifstream dataGame;
    std::string trim(std::string s);
public:
    GameState(const std::string &filename);

    std::string getOwner(const std::string &territoy);

    int getTanks(const std::string &territory);
  
    std::vector<std::string> getListTerrOfPlayer(const std::string &player);

    void loadData();
    
    std::vector<Attack> getPossibleAttacks(const std::string &player, Board &board);
};
#endif