#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/GameState.hpp"


GameState::GameState(const std::string &filename)
{
    this->fileName = filename;
    dataGame.open(fileName);
    if (!dataGame.is_open())
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


std::string GameState::getOwner(const std::string &territory)
{
    return info[territory].owner;
}

int GameState::getTanks(const std::string &territory)
{
    return info[territory].tanks;
}

void GameState::loadData()
{
    std::string line;

    while (getline(dataGame, line))
    {
        int pos = line.find(':');

        std::string state = trim(line.substr(0, pos));
        std::string other = trim(line.substr(pos + 1));

        int newPos = other.find(',');
        info[state].owner = other.substr(0, newPos);
        info[state].tanks = std::stoi(other.substr(newPos + 1));
    }
    
}
std::vector<std::string> GameState::getListTerrOfPlayer(const std::string &player)
{
    std::vector<std::string> risultato;
    for (auto& pair : info)  // stato = la tua map<string, TerritoryState>
    {
        if (pair.second.owner == player)
        {
            risultato.push_back(pair.first);
        }
    }
    return risultato;
}

std::vector<Attack> GameState::getPossibleAttacks(const std::string &player, Board &board)
{
    std::vector<Attack> result;
    std::vector<std::string> myTerritories = getListTerrOfPlayer(player);

    for(std::string terr : myTerritories){

        std::vector<std::string> neighbors = board.getVicini(terr);

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
