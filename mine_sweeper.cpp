#include <iostream>
#include "gameboard.h"
#include <cmath>

int main()
{
    int board_size;
    std::cout << "Welcome to Awseome Minesweeper!\n";
    
    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Not a valid number" << std::endl;
            }
            std::cout << "How many rows do you want the game board to have?" << std::endl;
            std::cin >> board_size;
    } while (board_size <= 0);

    Gameboard gameboard = Gameboard(board_size, board_size);

    for (size_t i = 0; i < 3; ++i) {
        gameboard.render();
        gameboard.chooseBox();
    }
    gameboard.render();

    return 0;
}

