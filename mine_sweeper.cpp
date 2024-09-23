#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "input.h"

//template<typename T>
//T getInput(const std::string& prompt) {
//    T input;
//    bool validInput = false;
//
//    while (!validInput) {
//        std::cout << prompt << std::endl;
//        std::cin >> input;
//
//        if (std::cin.fail()) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::cout << "Not a valid input, please try again." << std::endl;
//        }
//        else {
//            validInput = true;
//        }
//    }
//
//    return input;
//}

int main()
{
    std::srand(std::time(0));
    Input input = Input();
    std::cout << "Welcome to Awesome Minesweeper!\n";
    
    int board_size = 0;
    do {
        board_size = input.getInput<int>("How many rows do you want the game board to have?");
    } while (board_size <= 0 || board_size > 26); // limit set to 26 so that the maximum coordinates is z

    Gameboard gameboard = Gameboard(board_size, board_size);
    gameboard.randomizeMines();

    bool kaboom = false;
    int turns = board_size * board_size - board_size; //ersätt med en funktion som kollar om alla fria rutor är utforskade
    int t = 0; //antal spelade rundor
    char markChoice = 's';
    while (!kaboom && t < turns) {
        gameboard.render();
        markChoice = input.getInput<char>("Do you want to(e)xplore an area, (f)lag an area as dangerous or (s)ave the current map? (e/f/s)");
        switch (markChoice) {
            case 'e':
                kaboom = gameboard.exploreBox(markChoice);
                t++;
                break;
            case 'f':
                gameboard.flagBox(markChoice);
                break;
            case 's':
                std::cout << "This is a future feature, nothing saved" << std::endl;
                break;
            default:
                std::cout << "Invalid choice, please select (e), (f), or (s)." << std::endl;
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

