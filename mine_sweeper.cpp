#include <iostream>
#include "gameboard.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "input.h"
#include "fileManagement.h"

//TODO (if the project would have had more time and additional updates)
// the input class could handle some more of the error handling, reducing the lines here in the main class
// maybe change from only one predetermined save file to option for the player to create and name their own files
// clean the code,
//          some code could maybe be deleted or at least be more efficient
//          move stuff from main to relevant classes or new classes
//              both of the switch cases below could be rewritten with calls to new methods of functions
//          check if more methods and/or variables can be refactored
//              some of the methods in the gameboard class are somewhat clunky, refactor those



int main()
{
    std::srand(std::time(0));
    FileManagement fileManagment("mineSweeperSave.txt"); //create a new (or connect to an existing) save file

    //needed to initialize these variables here, because not possible to initialize in the following switch
    Input input(2, 2);
    Gameboard* gameboard = nullptr;
    char markChoice = 'a';
    int rows = 0;
    int columns = 0;
    int startingMines = 0;

    std::cout << "Welcome to Awesome Minesweeper!\n" << std::endl;
    while (markChoice != 's' && markChoice != 'c') {
        markChoice = input.getInput<char>("Do you want to (s)tart a new game or (c)ontinue a previous game? s/c ");
        switch (markChoice) {
        case 's':
            do { //the error handling could be handled separately if the getInput<> is upgraded. This would also reduce the amount of lines here. See the input-class
                rows = input.getInput<int>("How many rows do you want the game board to have?");
                columns = input.getInput<int>("How many columns do you want the game board to have?");
                startingMines = input.getInput<int>("How many mines do you want the game board to have?");
                if ((rows < 2 || rows > 26) || (columns < 2 || columns > 10) || (startingMines < 2 || startingMines >= rows*columns)) {
                    std::cout << "Rows need to be more than one and less then 27 \n and columns need to be more than 2 and less than 11 \n and mines need to be more than 1 and less than the amount of areas to explore\n" << std::endl;
                }
            } while ((rows < 2 || rows > 26) || (columns < 2 || columns > 10) || (startingMines < 2 || startingMines >= rows * columns));
            // row limit is set to 26 so that the maximum row never is more than 'z'
            //column limit is set to 10 because of the UI in the terminal is not user friendly for more than 10 columns with the current
                // render()-method in the gameboard class. Can be fixed so the column limit could be much higher

            //saving the values for the board size (rows and columns) so that the input object can use it's functions
            input.setRow(rows); 
            input.setColumn(columns);

            gameboard = new Gameboard(rows, columns, &input); //creating a new gameboard with the user´s input from above
            gameboard->randomizeMines(startingMines); //(move this to be called in the constructor instead)
                //kept it here to avoid bugs when loading a previous game
            break;
        case 'c': {
            std::istringstream stream = fileManagment.read(); //recieving the info from the save file
            std::string line;

            if (std::getline(stream, line)) {
                std::istringstream firstLine(line);
                firstLine >> rows >> columns; //getting the size for the gameboard
            }

            input.setRow(rows);
            input.setColumn(columns);

            gameboard = new Gameboard(rows, columns, &input); //creating the saved gameboard with the right size

            while (std::getline(stream, line)) { //loop that add the saved info into each cell on the board
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

    bool kaboom = false; //The player lose the game when this changes to true, which happens when a player trips on a mine (e.g. explore an area containing a mine
    int t = 0; //amount of turns the player has played
    while (!kaboom) {
        gameboard->render();
        std::cout << "Turn: " << t << std::endl;
        std::string coor = ""; //initializing needed to be outside the switch
        markChoice = input.getInput<char>("Do you want to (e)xplore a cell, (f)lag a cell as dangerous or (s)ave the current map? (e, f, s)");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (markChoice) {
        case 'e':
            coor = input.getInput<std::string>("which cell do you want to explore?");
            if (input.isValidCoor(coor)) {
                kaboom = gameboard->exploreCell(coor);
                t++;
                break;
            }
            else {
                std::cout << "Not a valid coordinate, please choose a valid coordinate \n" << std::endl;
                break;
            }
        case 'f':
            coor = input.getInput<std::string>("which cell do you want to flag?");
            if (input.isValidCoor(coor)) {
                gameboard->flagCell(coor);
                t++;
                break;
            }
            else {
                std::cout << "Not a valid coordinate, please choose a valid coordinate" << std::endl;
                break;
        case 's':
            gameboard->saveBoard("mineSweeperSave.txt");
            break;
        default:
            std::cout << "Not a valid option, please choose between e/f/s \n" << std::endl;
            break;
            }
        }

        if (kaboom) {
            gameboard->render();
            std::cout << "KABOOM! Game over" << std::endl;
        }
        if (gameboard->checkForVictory()) {
            gameboard->render();
            std::cout << "Congratz, you survived. This time..." << std::endl;
        }
    }
    delete gameboard;
    return 0;
}