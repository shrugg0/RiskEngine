#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "GameState.hpp"

struct StatsAttacks
{
    Attack atk;
    float winProb;
};

class Engine
{
private:
    std::vector<StatsAttacks> results;  
    
public:
    float EvaluateAttack(Attack atk, GameState& gs, int nSim);

    void EvaluateAllAttacks(std::string giocatore, GameState& stato, Board& board, int nSim);

    std::vector<StatsAttacks> GetResult();

    void PrintResult(); 
};

#endif