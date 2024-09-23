#pragma once
#include <string>
#include <vector>
#include <tuple>

class Gameboard {
private:
    std::vector<std::tuple<int, int, char, bool>> board; //changed [0] to int and nothing was detected in the functionality
    int row;
    int column;
    char starting_char = ' ';
    bool mine = false;
    int checkBoxes(std::pair<char, int>& coordinate);
    bool isValidCoor(std::pair<char, int>& coor) const;
    void expandZeroes(std::pair<char, int>& coor);
    std::pair<char, int> parseCoordinates(std::string& s) const;

public:
    Gameboard(int row, int column);
    void render() const;
    bool chooseBox();
    void randomizeMines();
    bool exploreBox(char& c);
    void flagBox(char& c);
};