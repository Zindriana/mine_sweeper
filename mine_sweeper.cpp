#include <iostream>
#include "gameboard.h"

int main()
{
    Gameboard gameboard = Gameboard();
    std::cout << "Welcome to Awseome Minesweeper!\n";
    gameboard.render(4, 4);
    //gameboard.mark();


    return 0;
}

