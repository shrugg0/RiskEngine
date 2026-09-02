#ifndef DICE_HPP
#define DICE_HPP

#include <array>

class Dice
{
private:
    int faces;
    int diceCount;
public:
    Dice();

    Dice(int faces);

    Dice(int faces, int diceToRoll);

    std::array<int, 3> roll();

    void setFaces(int faces);

    void setDiceCount(int newDiceCount);

    int getFaces() const;

    int getDiceCount() const;

};

#endif
