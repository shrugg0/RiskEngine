#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>


class Board
{
private:
    std::map<std::string, std::vector<std::string>>  adjList;
    std::ifstream datiBoard;
public:
    Board(const std::string& filename);
    void loadData();
    void getVicini(const std::string& state, std::vector<std::string>& vicini);
};


#endif
