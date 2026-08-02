#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/Dadi.hpp"




Battle::Battle(Army att, Army dif) : esercito1(att), esercito2(dif), dadoAtk(6,3), dadoDif(6,3) {};

std::string Battle::simulaRound()
{
    std::string winner;
    int atkLoses = 0, difLoses = 0;

    std::vector vecAtk = dadoAtk.Tira();
    std::vector vecDif = dadoDif.Tira();
/*
    std::cout << "Risultati dadi attaccante:" << std::endl;
    for (int n : vecAtk)
    {
        std::cout << n << " ";
    }
    std::cout << "\nRisultati dadi difensore:" << std::endl;
    for (int n : vecDif)
    {
        std::cout << n << " ";
    }
    */
 
    // ordinamento vettori
    std::sort(vecAtk.begin(), vecAtk.end(), [](int a, int b) { return a > b; });
    std::sort(vecDif.begin(), vecDif.end(), [](int a, int b) { return a > b; });

    //std::cout << "\n\nVettori ordinati e pronti per il confronto " << std::endl;

    std::cout << "Attaccante:" << std::endl;
    for (int n : vecAtk)
    {
        std::cout << n << " ";
    }
    std::cout << "\nDifensore:" << std::endl;
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
    
    std::cout << "\nPerdite lato attaccante: " << atkLoses << std::endl;
    std::cout << "Perdite lato difensore: " << difLoses << std::endl;
    

    if (atkLoses > difLoses)
    {
        winner = esercito2.getPlayer();
    }else{
        winner = esercito1.getPlayer();
    }
    return winner;
}

int Battle::getAtkTanks()
{
    return esercito1.getTanks();
}

int Battle::getDifTanks()
{
    return esercito2.getTanks();
}