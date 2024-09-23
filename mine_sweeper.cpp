#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "input.h"

int main()
{
    std::srand(std::time(0));
    Input input(2, 2);
    int board_size; //using board_size instead of separate row and column for the moment, implement different values in the future
    std::cout << "Welcome to Awesome Minesweeper!\n";
    
    do {
        board_size = input.getInput<int>("How many rows do you want the game board to have?");
        if (board_size < 2 || board_size > 26) {
            std::cout << "Rows need to be more than one and less then 27" << std::endl;
        }
    } while (board_size < 2 || board_size > 26); // limit is set to 26 so that the maximum row never is more than 'z'

    input.setRow(board_size); //saving the values for the board size so the input objekt can use it's function
    input.setColumn(board_size);
    Gameboard gameboard = Gameboard(board_size, board_size);
    gameboard.randomizeMines();

    bool kaboom = false;
    int turns = board_size * board_size - board_size - 1; //ersätt med en funktion som kollar om alla fria rutor är utforskade
    int t = 0; //antal spelade rundor
    //std::cout << " turns to survive: " << turns << std::endl;
    while (!kaboom && t < turns ) {
        gameboard.render();
        char markChoice = input.getInput<char>("Do you want to (e)xplore an area, (f)lag an area as dangerous or (s)ave the current map? (e, f, s)");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string coor = input.getInput<std::string>("which box do you want to mark?");
        switch(markChoice){ 
            case 'e':
                kaboom = gameboard.exploreBox(coor);
                t++;
                break;
            case 'f':
                gameboard.flagBox(coor);
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

