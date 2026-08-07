#include <iostream>

#include "RiskProbability.hpp"

int main()
{
    RiskProbability rp;
    int atk, dif;
    std::cout << "Attack:";
    std::cin >> atk;
    std::cout << "Difend:";
    std::cin >> dif;
    

    double p = rp.winProbability(atk, dif);

    std::cout << "Probabilità di conquista: " << p * 100 << "%\n";
}