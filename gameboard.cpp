#include "gameboard.h"
#include <string>
#include <iostream>

Gameboard::Gameboard() {
	a1 = ' ';
	a2 = ' ';
	a3 = ' ';
	b1 = ' ';
	b2 = ' ';
	b3 = ' ';
	c1 = ' ';
	c2 = ' ';
	c3 = ' ';
}


void Gameboard::render(int row, int column) const{
	std::cout << "  ";
	for (size_t c = 1; c <= column; c++) {
		std::cout << " - " << c ;
	}
	std::cout << std::endl;

	for (size_t r = 1; r <= row; r++) {
		std::cout << " ";
		std::cout << static_cast<char>('a' + r - 1);
		for (size_t c = 1; c <= column+1; c++) {
			std::cout << " | " << " ";
		}
		std::cout << std::endl;
		for (size_t c = 1; c <= column+1; c++) {
			if (c != 1) {
				std::cout << " - " << " ";
			}
			else {
				std::cout << "  " << "  ";
			}
		}
		std::cout << std::endl;
	}
}

void Gameboard::chooseBox() {
	std::string chosenBox = "";
	std::cout << "which box do you want to mark?" << std::endl;
	std::cin >> chosenBox;
	markBox(chosenBox);
}

void Gameboard::markBox(std::string s) {
	
}

int Gameboard::checkBoxes(std::string s) {
	int amountOfMines = 0;
	/*if () {
	logic to check if adjacent boxes has mines or not
	};*/
	return amountOfMines;
}