#include <iostream>
#include <vector>

#include "Army.hpp"

int main(void)
{
    Army esercito1("Nero", 30, 14);
    esercito1.updateTerritori("Bosnia");

    std::cout << "Esercito giocatore " << esercito1.getPlayer() << " : \n";


    std::cout << "Carri armati: " << esercito1.getTanks() << std::endl;
    std::cout << "Numero territori: " << esercito1.getNumberTerritori() << std::endl;
    esercito1.listTerritori();
    int tanksToAdd;
    std::string territorioToAdd;
    std::cout << "Quanti carri armati aggiungere? ";
    std::cin >> tanksToAdd;
    esercito1.updateTanks(tanksToAdd);
    std::cout << "Quale territorio aggiungere? ";
    std::cin >> territorioToAdd;
    esercito1.updateTerritori(territorioToAdd);

    std::cout << "Carri armati: " << esercito1.getTanks() << std::endl;
    esercito1.listTerritori();
}
