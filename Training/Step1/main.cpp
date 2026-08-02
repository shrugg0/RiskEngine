#include <bits/stdc++.h>
#include <vector>
#include <random>

#include "Dadi.hpp"

int main(void)
{
    Dadi dado(6);

    dado.setMultiply(3);

    std::cout << "Lancio di " << dado.getMultply() << " dadi da " << dado.getFaces() << " facce ciascuno..." << std::endl;

    std::cout << "Risultati:" << std::endl;

    for(int n : dado.Tira()){
        std::cout << n << " ";
    }
}