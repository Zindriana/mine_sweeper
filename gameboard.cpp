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
	std::cout << " ";
	for (size_t col = 0; col <= column; col++) {
		std::cout << " - - - " << " ";
	}
	std::cout << std::endl;
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