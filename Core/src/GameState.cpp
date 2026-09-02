#include <stdexcept>
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "../include/GameState.hpp"
#include "../include/Board.hpp"


GameState::GameState(const std::string &filename)
{
    this->fileName = filename;
    gameData.open(fileName);
    if (!gameData.is_open())
    {
        throw std::runtime_error("File not found -> " + fileName);
    }

}

std::string GameState::trim(std::string s)
{
    while (!s.empty() && s[0] == ' ')
        s.erase(0, 1);
    while (!s.empty() && s.back() == ' ')
        s.pop_back();
    return s;
}


std::string GameState::getOwner(const std::string &territory) const
{
    auto it = info.find(territory);
    if (it == info.end()) {
        throw std::runtime_error("There is a territory that is NOT in the database, plese check dataGame.txt with Board.txt");
    }
    return it->second.owner;
}

int GameState::getTanks(const std::string &territory) const
{
    auto it = info.find(territory);
    if (it == info.end()) {
        throw std::runtime_error("There is a territory that is NOT in the database, plese check dataGame.txt with Board.txt");
    }
    return it->second.tanks;
}

void GameState::loadData()
{
    std::string line;

    while (getline(gameData, line))
    {
        int pos = line.find(':');

        std::string state = trim(line.substr(0, pos));
        std::string other = trim(line.substr(pos + 1));

        int newPos = other.find(',');
        info[state].owner = other.substr(0, newPos);
        info[state].tanks = std::stoi(other.substr(newPos + 1));
    }

}
std::vector<std::string> GameState::getPlayerTerritories(const std::string &player) const
{
    std::vector<std::string> result;
    for (const auto& pair : info)
    {
        if (pair.second.owner == player)
        {
            result.push_back(pair.first);
        }
    }
    return result;
}

std::vector<Attack> GameState::getPossibleAttacks(const std::string &player, const Board &board) const
{
    std::vector<Attack> result;
    std::vector<std::string> myTerritories = getPlayerTerritories(player);

    for(std::string terr : myTerritories){

        std::vector<std::string> neighbors = board.getNeighbors(terr);

        for(std::string neighbor : neighbors)
        {
            if(getOwner(neighbor) != player)
            {
                result.push_back({terr, neighbor});
            }
        }
    }
    return result;
}
