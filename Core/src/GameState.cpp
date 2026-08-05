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

std::string GameState::getOwner(const std::string &territory)
{
    return std::string();
}

int GameState::getTanks(const std::string &territory)
{
    return 0;
}

std::vector<std::string> GameState::getListTerrOfPlayer(const std::string &territory)
{
    return std::vector<std::string>();
}
