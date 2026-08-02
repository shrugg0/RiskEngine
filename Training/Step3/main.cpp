#include <iostream>
#include <vector>
#include <algorithm>

#include "include/Army.hpp"
#include "include/Battle.hpp"
#include "include/Dadi.hpp"

int main(void){
    Army esercito1("Nero", 30, 0);
    Army esercito2("Rosso", 20, 0);

    Battle battle(esercito1, esercito2);
    std::string winner = battle.simulaRound();
    std::cout << "\n\nIl vincitore del round è il " << winner << std::endl;

    
    
}