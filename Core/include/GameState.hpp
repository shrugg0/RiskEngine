/* Who controls each territory, and how many tanks, rn ?  */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


struct TerritoryState {
    std::string owner;
    int tanks;
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
    
};
