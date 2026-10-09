#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "include/GameState.hpp"
#include "include/Board.hpp"
#include "include/Engine.hpp"

#define OK 0
#define FAILURE 1

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << argv[0] << ": Bad usage\n Try '" << argv[0] << " <player>' (Red, Blue, Yellow, Green, Black, Purple)\n";
        return FAILURE;
    }

    std::string inputPlayer = argv[1];
    if (!inputPlayer.empty()) {
        inputPlayer[0] = std::toupper(static_cast<unsigned char>(inputPlayer[0]));
        for (size_t i = 1; i < inputPlayer.size(); ++i) {
            inputPlayer[i] = std::tolower(static_cast<unsigned char>(inputPlayer[i]));
        }
    }

    std::vector<std::string> validPlayers = {"Red", "Yellow", "Blue", "Green", "Black", "Purple"};

    bool found = false;
    for (const std::string& p : validPlayers) {
        if (p == inputPlayer) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cerr << "Error: Player '" << argv[1] << "' does not exist.\n";
        return FAILURE;
    }

    Board board("Assets/Board.txt");
    GameState gs("Assets/dataGame.txt");
    Engine en;

    board.loadData();
    gs.loadData();

    en.evaluateAllAttacks(inputPlayer, gs, board);
    std::cout << "\n\n";
    en.printResults(inputPlayer);

    return OK;
}
