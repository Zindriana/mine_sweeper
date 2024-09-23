#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "input.h"

class Gameboard {
private:
    std::vector<std::tuple<int, int, char, bool>> board; //changed [0] to int from char, didn´t find any difference in functionality when testing code?
    int row;
    int column;
    char starting_char = ' ';
    bool mine = false;
    Input* input;
    int checkBoxes(std::string& s);
    void expandZeroes(std::string& s);

public:
    Gameboard(int row, int column, Input* input);
    void render() const;
    void randomizeMines();
    bool exploreBox(std::string& s);
    void flagBox(std::string& s);
    bool checkForVictory();
};