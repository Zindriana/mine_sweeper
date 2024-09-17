#pragma once
#include <string>

class Gameboard {
private:
    char a1;
    char a2;
    char a3;
    char b1;
    char b2;
    char b3;
    char c1;
    char c2;
    char c3;

public:
    Gameboard();
    void render(int row, int column) const;
    void chooseBox();
    void markBox(std::string s);
    int checkBoxes(std::string s);
};
