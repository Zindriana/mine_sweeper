#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "input.h"

class Gameboard {
private:
    std::vector<std::tuple<int, int, char, bool>> board; //changed [0] to int from char, didn´t find any difference in functionality when testing code
    int row;
    int column;
    char starting_char = '?';
    bool mine = false;
    Input* input;
    int checkCells(const std::string& s);
    void expandZeroes(const std::string& s);

public:
    Gameboard(const int row, const int column, const Input* input);
    void saveBoard(const std::string& filename);
    void render() const;
    void randomizeMines(const int amountOfMines); //maybe move this to private and move the call from main class to be called when initializing the Gameboard constructor
    bool exploreCell(const std::string& s);
    void flagCell(const std::string& s);
    bool checkForVictory();
    void setCell(const int x, const int y, const char value, const bool isMine);
};