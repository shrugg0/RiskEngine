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
    bool verbose;
    std::chrono::steady_clock::time_point startTime;

public:
    Engine(bool verbose);

    double evaluateAttack(Attack attack, GameState& gameState, int numSimulations);

    void evaluateAllAttacks(std::string player, GameState& gameState, Board& board, int numSimulations);

    std::vector<AttackStats> getResults() const;

    void printResults();
};

#endif
