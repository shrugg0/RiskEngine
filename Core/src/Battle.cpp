#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/Dadi.hpp"


Battle::Battle(Army att, Army dif) : esercito1(att), esercito2(dif), dadoAtk(6,3), dadoDif(6,3), diceCap(2) {};

std::string Battle::simulaRound()
{
    std::string winner;
    // Gestione numero dadi, ricalcolato ad ogni turno in base ai carri
    int diceAtk = std::min(3, esercito1.getTanks() - 1); 
    int diceDif = std::min(diceCap, esercito2.getTanks()); 

    dadoAtk.setMultiply(diceAtk);
    dadoDif.setMultiply(diceDif);
    int atkLoses = 0, difLoses = 0;

    std::vector vecAtk = dadoAtk.Tira();
    std::vector vecDif = dadoDif.Tira();

 
    // ordinamento vettori
    std::sort(vecAtk.begin(), vecAtk.end(), [](int a, int b) { return a > b; });
    std::sort(vecDif.begin(), vecDif.end(), [](int a, int b) { return a > b; });


    std::cout << "Attacker:" << std::endl;
    for (int n : vecAtk)
    {
        std::cout << n << " ";
    }
    std::cout << "\nDefender:" << std::endl;
    for (int n : vecDif)
    {
        std::cout << n << " ";
    }

    for (size_t i = 0; i < std::min(vecAtk.size(), vecDif.size()); i++)
    {
        if (vecAtk[i] <= vecDif[i])
        {
            atkLoses++;
        }else{
            difLoses++;
        }
    }
    esercito1.updateTanks(-atkLoses); 
    esercito2.updateTanks(-difLoses); 
    
    std::cout << "\nLoses attacker's side: " << atkLoses << std::endl;
    std::cout << "Loses defender's side: " << difLoses << std::endl;

    std::cout << "Tanks left on the attacker's territory :" << esercito1.getTanks() << std::endl;
    std::cout << "Tanks left on the defender's territory :" << esercito2.getTanks() << std::endl;
    
    

    if (atkLoses > difLoses)
    {
        winner = esercito2.getPlayer();    
    }else if (atkLoses < difLoses){
        winner = esercito1.getPlayer();
    }else{
        winner = "Tie";
    }  
    return winner;
}
void Battle::setDiceCap()
{
    int newCap;
    do
    {
        std::cout << "\nNew dice cap ( 2 or 3 ): ";
        std::cin >> newCap;
    } while (newCap != 2 && newCap != 3);
    
    this->diceCap = newCap;
}

int Battle::getAtkTanks()
{
    return esercito1.getTanks();
}

int Battle::getDifTanks()
{
    return esercito2.getTanks();
}

