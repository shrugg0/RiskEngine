#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>


class Board
{
private:
    std::string fileName;
    std::map<std::string, std::vector<std::string>>  adjList;
    std::ifstream boardData;
    std::string trim(std::string s);
public:
    Board(const std::string& filename);

    void loadData();

    std::vector<std::string> getNeighbors(const std::string& state) const;

    void printBoard() const;

    void printNeighbors(const std::string &state) const;
};


#endif
