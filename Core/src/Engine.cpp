#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "../include/GameState.hpp"
#include "../include/Board.hpp"
#include "../include/Engine.hpp"
#include "../include/Army.hpp"
#include "../include/MonteCarlo.hpp"

Engine::Engine(bool verbose) : verbose(verbose), startTime(std::chrono::steady_clock::now()) {};

double Engine::evaluateAttack(Attack attack, GameState &gameState, int numSimulations)
{
    Army atk(gameState.getOwner(attack.from), gameState.getTanks(attack.from));
    Army dif(gameState.getOwner(attack.to), gameState.getTanks(attack.to));

    MonteCarlo mc(atk, dif, numSimulations, verbose);
    mc.runSimulations();

    return mc.getWinRate();
}

void Engine::evaluateAllAttacks(std::string player, GameState &gameState, Board &board, int numSimulations)
{
    results.clear();
    std::vector<Attack> attacks = gameState.getPossibleAttacks(player, board);

    for (Attack a : attacks)
    {
        double prob = evaluateAttack(a, gameState, numSimulations);
        results.push_back({a, prob});
    }
}
std::vector<AttackStats> Engine::getResults() const
{
    return results;
}

void Engine::printResults()
{
    std::sort(results.begin(), results.end(), [](const AttackStats a, const AttackStats b){ return a.winProbability > b.winProbability;});
    for(AttackStats sa : results){
        std::cout << "Attacking from " << sa.attack.from << " the territory " << sa.attack.to << " you have a " << sa.winProbability << "% of winning" << std::endl;
    }
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "\nEvaluation done in: " << duration.count() << " ms" << std::endl;
}
