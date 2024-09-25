#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "input.h"
#include "fileManagement.h"

//TODO 
// PRIO! = function to save and load the game
// implement so that the user can choose different amount of rows, columns and mines
// clean the code
// be one with the code



int main()
{
    std::srand(std::time(0));
    Input input(2, 2);
    FileManagement fileManagment("testSave.txt");
    Gameboard* gameboard = nullptr; // needed this because of not being able to initialize gameboard in switch
    int board_size; //using board_size instead of separate row and column for the moment, implement different values in the future
    char markChoice = input.getInput<char>("Welcome to Awesome Minesweeper!\n Do you want to (s)tart a new game or (c)ontinue a previous game? s/c ");
    std::istringstream iss = fileManagment.read();
    std::string line;
    std::istringstream cellStream(line);
    do
        switch (markChoice) {
            case 's':
                do {
                    board_size = input.getInput<int>("How many rows do you want the game board to have?");
                    if (board_size < 2 || board_size > 26) {
                        std::cout << "Rows need to be more than one and less then 27" << std::endl;
                    }
                } while (board_size < 2 || board_size > 26); // limit is set to 26 so that the maximum row never is more than 'z'

                input.setRow(board_size); //saving the values for the board size so that the input object can use it's functions
                input.setColumn(board_size);
                gameboard = new Gameboard(board_size, board_size, &input);
                gameboard->randomizeMines(); //move this to be called in the constructor instead
                break;
            case 'c': {
                std::istringstream iss = fileManagment.read();
                std::string line;
                int rows;
                int columns;

                if (std::getline(iss, line)) {
                    std::istringstream firstLine(line);
                    firstLine >> rows >> columns;
                }

                input.setRow(rows);
                input.setColumn(columns);
                gameboard = new Gameboard(rows, columns, &input);

                while (std::getline(iss, line)) {
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
    } while (markChoice != 's' && markChoice != 'c');

    bool kaboom = false;
    bool foundAllMines = false;
    int t = 0;
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
            std::cout << "Game board is saved \n" << std::endl;
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