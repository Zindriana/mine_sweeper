#pragma once
#include <string>
#include <iostream>

class Input
{

private:
    int row;
    int column;

public:

    Input(int row, int column);
    bool isValidCoor(const std::string& s) const;
    std::pair<char, int> parseCoordinates(const std::string& s) const;
    void setRow(int r);
    void setColumn(int c);

    template<typename T>
    T getInput(const std::string& prompt) { //could add a second parameter here with a validation argument, for example legit range for int.
        //This sould create better error handling and would reduce the amount of lines in the main class
        T input;
        bool validInput = false;

        while (!validInput) {
            std::cout << prompt << std::endl;
            std::cin >> input;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Not a valid input, please try again." << std::endl;
            }
            else {
                validInput = true;
            }
        }

        return input;
    }
};

