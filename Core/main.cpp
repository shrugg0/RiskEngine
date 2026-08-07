#define OK 0
#define FAILURE 1

#include <iostream>
#include <string>

#include "include/MonteCarlo.hpp"
#include "include/GameState.hpp"
#include "include/Board.hpp"
#include "include/Engine.hpp"
#include "include/Battle.hpp"

int main(void)
{

    Board board("Assets/Board.txt");
    GameState gs("Assets/dataGame.txt");
    Engine en;

    std::string player = "Red";
    int nSim = 10000;

    board.loadData();
    gs.loadData();

    Attack atk;
    atk.from = "Alaska";
    atk.to = "Northwest Territory";

    en.EvaluateAllAttacks(player, gs, board, nSim);
    std::cout << "\n\n";
    en.PrintResult();
    
    return OK;
}