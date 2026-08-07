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
    int nSim;

    board.loadData();
    gs.loadData();

    std::cout << "How many simulation for each battle ( state vs state, 10000 recommended ): ";
    std::cin >> nSim;

    en.EvaluateAllAttacks(player, gs, board, nSim);
    std::cout << "\n\n";
    en.PrintResult();
    
    return OK;
}