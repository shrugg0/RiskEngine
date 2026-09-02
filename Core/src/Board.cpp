#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/Board.hpp"

Board::Board(const std::string& filename) 
{
    this->fileName = filename;
    boardData.open(filename);
    if (!boardData.is_open())
    {
        throw std::runtime_error("File not found -> " + filename);
    }
}

std::string Board::trim(std::string s)
{
    while (!s.empty() && s[0] == ' ')
        s.erase(0, 1);
    while (!s.empty() && s.back() == ' ')
        s.pop_back();
    return s;
}

void Board::printBoard(){
    for(const auto& [key, value] : adjList){
        std::cout << key << " - ";
        for(const auto& state : value){
            std::cout << state << ", ";
        }
        std::cout << std::endl;
    }
}

void Board::loadData()
{
    std::string line;
    
    while (std::getline(boardData, line))
    {
        size_t pos = line.find(':');

        std::string node = trim(line.substr(0, pos));
        std::string adjacents = line.substr(pos + 1);

        std::vector<std::string> neighbors;

        std::stringstream ss(adjacents);
        std::string neighbor;

        while (getline(ss, neighbor, ',')) {
            neighbors.push_back(trim(neighbor));
        }

        adjList[node] = neighbors;
    }
}
    

// reference used here : https://en.cppreference.com/cpp/container/map/find
std::vector<std::string> Board::getNeighbors(const std::string &state)
{
    if (auto search = adjList.find(state) ; search != adjList.end())
    {
        return adjList[state];
    }else{
        return {};
    }
}

void Board::printNeighbors(const std::string &state)
{
    if (auto search = adjList.find(state) ; search != adjList.end())
    {
        for(const auto& v : adjList[state]){
            std::cout << v << " ";
        }
    }
}
