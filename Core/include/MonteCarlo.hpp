#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <string>
#include <map>

#include "Army.hpp"

class MonteCarlo
{
private:
    Army attackerArmy;
    Army defenderArmy;
    int simulations;
    bool verbose;
    std::map<std::string, int> stats;
public:
    MonteCarlo(Army atk, Army dif, int n, bool verbose);

    std::string simulateBattle();

    void runSimulations();

    void printStats();

    double getWinRate();
};
#endif
