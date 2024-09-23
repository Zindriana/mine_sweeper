#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "input.h"

int main()
{
    std::srand(std::time(0));
    Input input;
    int board_size;
    std::cout << "Welcome to Awesome Minesweeper!\n";
    
    do {
        board_size = input.getInput<int>("How many rows do you want the game board to have?");
        if (board_size < 0 || board_size > 26) {
            std::cout << "Rows need to be more than one and less then 27" << std::endl;
        }
    } while (board_size < 0 || board_size > 26); // limit is set to 26 so that the maximum row never is more than 'z'


    Gameboard gameboard = Gameboard(board_size, board_size);
    gameboard.randomizeMines();

    bool kaboom = false;
    int turns = board_size * board_size - board_size - 1; //ersätt med en funktion som kollar om alla fria rutor är utforskade
    int t = 0; //antal spelade rundor
    //std::cout << " turns to survive: " << turns << std::endl;
    while (!kaboom && t < turns ) {
        gameboard.render();
        char markChoice;
        markChoice = input.getInput<char>("Do you want to (e)xplore an area, (f)lag an area as dangerous or (s)ave the current map? (e, f, s)");
        switch(markChoice){
            case 'e':
                kaboom = gameboard.chooseBox('e');
                t++;
                break;
            case 'f':
                gameboard.chooseBox('f');
                break;
            case 's':
                std::cout << "Future feature, nothing is saved" << std::endl;
                break;
            default:
                break;
        }
        
    }
    
    gameboard.render();
    if (kaboom) {
        std::cout << "KABOOM! Game over" << std::endl;
    } else {
        std::cout << "Congratz, you survived. This time..." << std::endl;
    }
    

    return 0;
}

