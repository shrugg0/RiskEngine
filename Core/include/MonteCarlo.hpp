#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <string>
#include <map>

#include "Army.hpp"

class MonteCarlo
{
private:
    Army esercito1;
    Army esercito2;
    int sims;
    bool verbose;
    std::map<std::string, int> stats;
public:
    MonteCarlo(Army atk, Army dif, int n, bool verbose);

    std::string SimulaBattle();

    void RunnaSimulazioni();

    void PrintStats();

    double getWinRate();
};
#endif
