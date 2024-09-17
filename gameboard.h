#pragma once
#include <string>
#include <vector>
#include <tuple>

class Gameboard {
private:
    std::vector<std::tuple<char, int, char>> board;
    int row;
    int column;
    char starting_char = ' ';

public:
    Gameboard(int row, int column);
    void render() const;
    void chooseBox();
    void markBox(std::string s);
    int checkBoxes(std::string s);
};