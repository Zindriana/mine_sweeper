#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

int main()
{
    std::srand(std::time(0));
    int board_size;
    std::cout << "Welcome to Awesome Minesweeper!\n";
    
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
    int turns = board_size * board_size - board_size; //ersätt med en funktion som kollar om alla fria rutor är utforskade
    int t = 0; //antal spelade rundor
    std::cout << " turns to survive: " << turns << std::endl;
    while (!kaboom && t < turns ) {
        gameboard.render();
        char markChoice;
        std::cout << "Do you want to explore an area or flag an area as dangerous? (e or f)" << std::endl;
        std::cin >> markChoice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Not a valid character" << std::endl;
        }
        if (markChoice == 'e' || markChoice == 'f') { //gör om till switch. Lägg till sparalternativ
            kaboom = gameboard.chooseBox(markChoice); //kalla istället på explore/flag/save
            if(markChoice == 'e'){
                ++t;
                std::cout << " turns played: " << t << std::endl;
            }  
        } else {
            std::cout << "Not a legit choice, choose again" << std::endl;
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

