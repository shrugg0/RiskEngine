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


double Engine::EvaluateAttack(Attack atkStruct, GameState &gs, int nSim)
{
    Army atk(gs.getOwner(atkStruct.from), gs.getTanks(atkStruct.from));
    Army dif(gs.getOwner(atkStruct.to), gs.getTanks(atkStruct.to));

    MonteCarlo mc(atk,dif,nSim);
    mc.RunnaSimulazioni();

    return mc.getWinRate();
}

void Engine::EvaluateAllAttacks(std::string giocatore, GameState &stato, Board &board, int nSim)
{
    results.clear();
    std::vector<Attack> attacchi = stato.getPossibleAttacks(giocatore, board);
    
    for (Attack a : attacchi)
    {
        double prob = EvaluateAttack(a, stato, nSim);
        results.push_back({a, prob});
    }
}
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
