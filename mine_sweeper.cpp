#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

int main()
{
    std::srand(std::time(0));
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
    gameboard.randomizeMines();

    bool kaboom = false;
    int turns = board_size * board_size - board_size; //antalet turns som behöver spelas innan spelet är vunnet
    int t = 0; //antal spelade rundor
    while (!kaboom && t < turns ) {
        gameboard.render();
        kaboom = gameboard.chooseBox();
        ++t;
    }
    
    gameboard.render();
    if (kaboom) {
        std::cout << "KABOOM! Game over" << std::endl;
    } else {
        std::cout << "Grattis, du överlevde. För den här gången :D" << std::endl;
    }
    

    return 0;
}

