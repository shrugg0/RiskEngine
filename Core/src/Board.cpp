#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "../include/Board.hpp"

Board::Board(const std::string& filename) 
{
    datiBoard.open(filename);
    if (!datiBoard.is_open())
    {
        throw std::runtime_error("File not found -> " + filename);
    }
    
}

void Board::loadData()
{
    
}

void Board::getVicini(const std::string &state, std::vector<std::string> &vicini)
{
}
