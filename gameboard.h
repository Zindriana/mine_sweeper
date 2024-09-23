#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "input.h"

class Gameboard {
private:
    std::vector<std::tuple<int, int, char, bool>> board; //[0] to int?
    int row;
    int column;
    char starting_char = ' ';
    bool mine = false;
    Input* input;
    int checkBoxes(std::string& s);
    bool isValidCoor(std::string& s) const;
    void expandZeroes(std::string& s);
    std::pair<char, int> parseCoordinates(std::string& s) const;

public:
    Gameboard(int row, int column, Input* input);
    void render() const;
    //bool chooseBox(char c);
    void randomizeMines();
    bool exploreBox(std::string& s);
    void flagBox(std::string& s);
};