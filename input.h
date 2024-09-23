#pragma once
#include <string>
#include <iostream>

class Input
{

private: 

public:

    template<typename T>
    T getInput(const std::string& prompt) {
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

