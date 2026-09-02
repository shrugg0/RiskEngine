#ifndef DICE_HPP
#define DICE_HPP

#include <vector>

class Dice
{
private:
    int faces;
    int diceCount;
public:
    Dice();

    Dice(int faces);

    Dice(int faces, int diceToRoll);

    std::vector<int> roll();

    void setFaces(int faces);

    void setDiceCount(int newDiceCount);

    int getFaces();

    int getDiceCount();

};

#endif
