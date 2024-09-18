#pragma once
#include <string>
#include <vector>
#include <tuple>

class Gameboard {
private:
    std::vector<std::tuple<char, int, char, bool>> board;
    int row;
    int column;
    char starting_char = ' ';
    bool mine = false;

public:
    Gameboard(int row, int column);
    void render() const;
    void chooseBox();
    void markBox(std::string& s);
    int checkBoxes(std::string& s);
    bool isValidCoor(std::string& s) const;
    std::pair<char, int> parseCoordinates(std::string& s) const;
    void randomizeMines();
};