#ifndef DADI_HPP
#define DADI_HPP

#include <bits/stdc++.h>

class Dadi
{
private:
    int faces;
    int multiply;
public:
    Dadi();

    Dadi(int faces);

    Dadi(int faces, int dadiDaTirare);
    
    std::vector<int> Tira();

    void setFaces(int faces);

    void setMultiply(int newMultiply);

    int getFaces();

    int getMultply();

};

#endif