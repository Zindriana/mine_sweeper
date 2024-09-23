#pragma once
#include <string>
#include <vector>
#include <tuple>

class Gameboard {
private:
    std::vector<std::tuple<char, int, char, bool>> board; //[0] to int?
    int row;
    int column;
    char starting_char = ' ';
    bool mine = false;
    int checkBoxes(std::string& s);
    bool isValidCoor(std::string& s) const;
    void expandZeroes(std::string& s);
    std::pair<char, int> parseCoordinates(std::string& s) const;

public:
    Gameboard(int row, int column);
    void render() const;
    //bool chooseBox(char c);
    void randomizeMines();
    bool exploreBox(std::string& s);
    void flagBox(std::string& s);
};