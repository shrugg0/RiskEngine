#include <bits/stdc++.h>
#include <vector>
#include <random>

#include "Dadi.hpp"

Dadi::Dadi(){
    faces = 6;
    multiply = 1;
}

Dadi::Dadi(int faces){
    this->faces = faces;
}

Dadi::Dadi(int faces, int dadiDaTirare){
    this->faces = faces;
    this->multiply = dadiDaTirare;
}

std::vector<int> Dadi::Tira()
{
    std::vector<int> ris;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1,faces);

    for(size_t i = 0; i < multiply; i++){
        ris.push_back(distrib(gen));
    }

    return ris;
}

void Dadi::setFaces(int faces)
{
    this->faces = faces;
}

void Dadi::setMultiply(int newMultiply)
{
    this->multiply = newMultiply;
}

int Dadi::getFaces()
{
    return this->faces;
}

int Dadi::getMultply()
{
    return this->multiply;
}
