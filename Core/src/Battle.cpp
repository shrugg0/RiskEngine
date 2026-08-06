#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/Army.hpp"
#include "../include/Battle.hpp"
#include "../include/Dadi.hpp"



//! nuova istanza di Battle per ogni scontro ? 
//! se si strcut attacks al posto di esercito1 e esercito2, se no simula round deve prendere come parametro attacks
Battle::Battle(Army att, Army dif) : esercito1(att), esercito2(dif), dadoAtk(6,3), dadoDif(6,3) {};

std::string Battle::simulaRound()
{
    std::string winner;
    // Gestione numero dadi, ricalcolato ad ogni turno in base ai carri
    int diceAtk = std::min(3, esercito1.getTanks() - 1); //! Da sostituire con i tanks di from.tanks ( struct Attack in GameState.hpp)
    int diceDif = std::min(3, esercito2.getTanks()); //! Da sostituire con i tanks di to.tanks ( struct Attack in GameState.hpp)

    dadoAtk.setMultiply(diceAtk);
    dadoDif.setMultiply(diceDif);
    int atkLoses = 0, difLoses = 0;

    std::vector vecAtk = dadoAtk.Tira();
    std::vector vecDif = dadoDif.Tira();

 
    // ordinamento vettori
    std::sort(vecAtk.begin(), vecAtk.end(), [](int a, int b) { return a > b; });
    std::sort(vecDif.begin(), vecDif.end(), [](int a, int b) { return a > b; });


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
    esercito1.updateTanks(-atkLoses); //! from.tanks =- loses
    esercito2.updateTanks(-difLoses); //! to.tanks =- loses
    
    std::cout << "\nPerdite lato attaccante: " << atkLoses << std::endl;
    std::cout << "Perdite lato difensore: " << difLoses << std::endl;
    

    if (atkLoses > difLoses)
    {
        winner = esercito2.getPlayer();    //! winner = to.owner
    }else{
        winner = esercito1.getPlayer(); //! winnwer = from.owner
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