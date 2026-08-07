#pragma once
#include <vector>
#include <map>

struct Transition {
    int attackerLoss;
    int defenderLoss;
    double probability;
};

class RiskProbability {
public:
    RiskProbability();
    double winProbability(int attackers, int defenders);

private:
    std::vector<std::vector<double>> memo;
    std::vector<std::vector<bool>> computed;
    std::map<std::pair<int,int>, std::vector<Transition>> transitions;

    double solve(int a, int d);
};
