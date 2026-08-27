#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>

#include "GameState.hpp"

struct StatsAttacks
{
    Attack atk;
    double winProb;
};

class Engine
{
private:
    std::vector<StatsAttacks> results;

public:
    double EvaluateAttack(Attack atk, GameState& gs, int nSim);

    void EvaluateAllAttacks(std::string giocatore, GameState& stato, Board& board, int nSim);

    std::vector<StatsAttacks> GetResult();

    void PrintResult();
};

#endif
