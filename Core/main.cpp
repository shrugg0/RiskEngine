#include <iostream>
#include <string>

#include "include/GameState.hpp"
#include "include/Board.hpp"
#include "include/Engine.hpp"

#define OK 0
#define FAILURE 1

int main(/*int argc, char *argv[]*/)
{

    Board board("Assets/Board.txt");
    GameState gs("Assets/dataGame.txt");
    Engine en;

    std::string player = "Red"; // Dynamic player
    //int nSim = std::stoi(argv[1]);


    board.loadData();
    gs.loadData();

    en.evaluateAllAttacks(player, gs, board);
    std::cout << "\n\n";
    en.printResults();

    return OK;
}
