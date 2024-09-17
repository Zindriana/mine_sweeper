#include <iostream>
#include "gameboard.h"

int main()
{
    int board_size = 1;
    std::cout << "Welcome to Awseome Minesweeper!\n";
    std::cout << "How big do you want the game board to be?" << std::endl;
    std::cin >> board_size;
    Gameboard gameboard = Gameboard(board_size, board_size);
    gameboard.render();
    gameboard.chooseBox();
    gameboard.render();


    return 0;
}

