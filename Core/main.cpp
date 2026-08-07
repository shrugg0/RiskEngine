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
    int nSim = 10;

    board.loadData();
    gs.loadData();

    Attack atk;
    atk.from = "Alaska";
    atk.to = "Northwest Territory";
/*
    float winProb = en.EvaluateAttack(atk, gs, nSim);

    std::cout << "Probabilità di conquista territorio : " << winProb << std::endl;

    */
    Army attk(gs.getOwner(atk.from), 4);
    Army dif(gs.getOwner(atk.to), 2);
    Battle b(attk, dif);
    for (size_t i = 0; i < 1000; i++)
    {
        std::cout << "Winner : " << b.simulaRound() << "\n\n";
    }

    
    return OK;
}