#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/GameState.hpp"
#include "../include/Board.hpp"
#include "../include/Engine.hpp"
#include "../include/Army.hpp"
#include "../include/MonteCarlo.hpp"


float Engine::EvaluateAttack(Attack atkStruct, GameState &gs, int nSim)
{
    Army atk(gs.getOwner(atkStruct.from), gs.getTanks(atkStruct.from));
    Army dif(gs.getOwner(atkStruct.to), gs.getTanks(atkStruct.to));

    MonteCarlo mc(atk,dif,nSim);
    mc.RunnaSimulazioni();

    return mc.getWinRate();
}

void Engine::EvaluateAllAttacks(std::string giocatore, GameState &stato, Board &board, int nSim)
{
    std::vector<Attack> attacchi = stato.getPossibleAttacks(giocatore, board);
    
    for (Attack a : attacchi)
    {
        float prob = EvaluateAttack(a, stato, nSim);
        results.push_back({a, prob});
    }
}
// Attaccando da StatsAttacks.atk.from a StatsAttacks.atk.to al StatsAttacks.winProb vinci
// std::sort(result.begin(),result.end(), [](float a, float b) { return })
//std::sort(vecAtk.begin(), vecAtk.end(), [](int a, int b) { return a > b; });
std::vector<StatsAttacks> Engine::GetResult()
{
    return results;
}

void Engine::PrintResult()
{
    std::sort(results.begin(), results.end(), [](const StatsAttacks a, const StatsAttacks b){ return a.winProb > b.winProb;});
    for(StatsAttacks sa : results){
        std::cout << "Attaccando da " << sa.atk.from << " il territorio " << sa.atk.to << " hai il " << sa.winProb << "% di vittoria" << std::endl;
    }
}
