#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>
#include <chrono>

#include "GameState.hpp"

struct AttackStats
{
    Attack attack;
    double winProbability;
};

class Engine
{
private:
    std::vector<AttackStats> results;
    std::chrono::steady_clock::time_point startTime;

public:
    Engine();

    double evaluateAttack(const Attack& attack,const GameState& gameState);

    void evaluateAllAttacks(const std::string& player, const GameState& gameState, const Board& board);

    std::vector<AttackStats> getResults() const;

    void printResults();
};

#endif
