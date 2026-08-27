#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <map>
#include <chrono>

#include "Army.hpp"

class MonteCarlo
{
private:
    Army esercito1;
    Army esercito2;
    int sims;
    std::map<std::string, int> stats;
    std::chrono::steady_clock::time_point startTime;
public:
    MonteCarlo(Army atk, Army dif, int n);

    std::string SimulaBattle();

    void RunnaSimulazioni();

    void PrintStats();

    double getWinRate();
};
#endif
