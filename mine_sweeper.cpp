#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "input.h"
#include "fileManagement.h"

//TODO 
// go through the code and add destructor and delete where needed
// add error handling to save and load methods
// implement so that the user can choose different amount of rows, columns and mines
// clean the code,
//          some code can probably be deleted
//          move stuff from main to relevant classes or new classes
//          control if some public methods instead can be private
//          check if some parameters in method can be set to const
//          check if methods and/or variables can be refactored
// be one with the code



int main()
{
    std::srand(std::time(0));
    FileManagement fileManagment("testSave.txt");

    //needed to initialize these variables here, because not possible to initialize in the following switch
    Input input(2, 2);
    Gameboard* gameboard = nullptr;
    char markChoice = 'a';
    int board_size; //using board_size instead of separate row and column for the moment, implement different values in the future

    std::cout << "Welcome to Awesome Minesweeper!\n" << std::endl;
    while (markChoice != 's' && markChoice != 'c') {
        markChoice = input.getInput<char>("Do you want to (s)tart a new game or (c)ontinue a previous game? s/c ");
        switch (markChoice) {
        case 's':
            do {
                board_size = input.getInput<int>("How many rows do you want the game board to have?");
                if (board_size < 2 || board_size > 26) {
                    std::cout << "Rows need to be more than one and less then 27" << std::endl;
                }
            } while (board_size < 2 || board_size > 26); // limit is set to 26 so that the maximum row never is more than 'z'

            //saving the values for the board size so that the input object can use it's functions
            input.setRow(board_size); 
            input.setColumn(board_size);

            gameboard = new Gameboard(board_size, board_size, &input);
            gameboard->randomizeMines(); //move this to be called in the constructor instead
            break;
        case 'c': {
            std::istringstream stream = fileManagment.read();
            std::string line;

            //these two can be moved to outside of the switch when implementing the option for different ranges for row and column
            int rows = 0;
            int columns = 0;

            if (std::getline(stream, line)) {
                std::istringstream firstLine(line);
                firstLine >> rows >> columns;
            }

            input.setRow(rows);
            input.setColumn(columns);

            gameboard = new Gameboard(rows, columns, &input);

            while (std::getline(stream, line)) {
                std::istringstream cellStream(line);
                int r, c;
                char value;
                bool isMine;
                cellStream >> r >> c >> value >> isMine;
                gameboard->setCell(r, c, value, isMine);
            }
            break;
        }
        default:
            std::cout << "Not a valid option, please choose between s/c \n" << std::endl;
            break;
        }
    }

    bool kaboom = false;
    bool foundAllMines = false;
    int t = 0; //amount of turns the player has played
    while (!kaboom && !foundAllMines) {
        gameboard->render();
        std::string coor = "";
        markChoice = input.getInput<char>("Do you want to (e)xplore an area, (f)lag an area as dangerous or (s)ave the current map? (e, f, s)");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (markChoice) {
        case 'e':
            coor = input.getInput<std::string>("which box do you want to explore?");
            if (input.isValidCoor(coor)) {
                kaboom = gameboard->exploreBox(coor);
                t++;
                std::cout << "Played turns: " << t << std::endl;
                break;
            }
            else {
                std::cout << "Not a valid coordinate, please choose a valid coordinate \n" << std::endl;
                break;
            }
        case 'f':
            coor = input.getInput<std::string>("which box do you want to flag?");
            if (input.isValidCoor(coor)) {
                gameboard->flagBox(coor);
                t++;
                std::cout << "Played turns: " << t << std::endl;
                break;
            }
            else {
                std::cout << "Not a valid coordinate, please choose a valid coordinate" << std::endl;
                break;
        case 's':
            gameboard->saveBoard("testSave.txt");
            std::cout << "Game board is saved \n" << std::endl; //this line can be moved to the saveBoard
            break;
        default:
            std::cout << "Not a valid option, please choose between e/f/s \n" << std::endl;
            break;
            }
        }

        foundAllMines = gameboard->checkForVictory();
        if (kaboom) {
            gameboard->render();
            std::cout << "KABOOM! Game over" << std::endl;
        }
        if (foundAllMines) {
            gameboard->render();
            std::cout << "Congratz, you survived. This time..." << std::endl;
        }
    }
    return 0;
}