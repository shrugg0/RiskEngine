#include <cctype>
#include <cstring>
#define OK 0
#define FAILURE 1

#include <iostream>
#include <string>

#include "include/GameState.hpp"
#include "include/Board.hpp"
#include "include/Engine.hpp"

bool checkSims(const std::string& str);

int main(int argc, char *argv[])
{
    bool verbose = false;

    if (argc == 1 || argc > 3)
    {
        std::cerr << "Usage: " << argv[0] << " <nSim> [-v|--verbose]\n";
        return FAILURE;
    }
    bool valid = checkSims(argv[1]);
    if (!valid)
    {
        std::cerr << "Usage: " << argv[0] << " <nSim> [-v|--verbose]\n";
        return FAILURE;
    }

    if (argc == 3)
    {
        if (strcmp(argv[2], "-v") == 0 || strcmp(argv[2], "--verbose") == 0)
        {
            verbose = true;
        }
        else
        {
            std::cerr << "Usage: " << argv[0] << " <nSim> [-v|--verbose]\n";
            return FAILURE;
        }
    }

    Board board("Assets/Board.txt");
    GameState gs("Assets/dataGame.txt");
    Engine en(verbose);

    std::string player = "Red";
    int nSim = std::stoi(argv[1]);


    board.loadData();
    gs.loadData();

    en.EvaluateAllAttacks(player, gs, board, nSim);
    std::cout << "\n\n";
    en.PrintResult();

    return OK;
}

bool checkSims(const std::string& str)
{
    if(str.empty()) { return false;}
    for(char c : str)
    {
        if(!std::isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}
