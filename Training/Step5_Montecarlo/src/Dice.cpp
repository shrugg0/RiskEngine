#include <random>
#include <chrono>

#include "../include/Dice.hpp"

Dice::Dice(){
    faces = 6;
    diceCount = 1;
}

Dice::Dice(int faces){
    this->faces = faces;
}

Dice::Dice(int faces, int diceToRoll){
    this->faces = faces;
    this->diceCount = diceToRoll;
}

std::array<int, 3> Dice::roll()
{
    std::array<int, 3> results = {0};

    static std::random_device rd;
    static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(1, faces);

    for(size_t i = 0; i < diceCount; i++){
        results[i] = distrib(gen);
    }

    return results;
}

void Dice::setFaces(int faces)
{
    this->faces = faces;
}

void Dice::setDiceCount(int newDiceCount)
{
    this->diceCount = newDiceCount;
}

int Dice::getFaces() const
{
    return this->faces;
}

int Dice::getDiceCount() const
{
    return this->diceCount;
}
