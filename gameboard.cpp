#include "gameboard.h"
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <cctype>
#include "mine.h"

Gameboard::Gameboard(int row, int column) : row(row), column(column) {
	for (char r = 'a'; r <= 'a' + row; ++r) { //preincrement är effektivare
		for (size_t c = 1; c <= column; ++c) { //postincrement behöver skapa en kopia först
			board.push_back(std::make_tuple(r, c, starting_char, mine));
		}
		Mine minefield = Mine();
		minefield.randomizeMines();
	}
}

void Gameboard::render() const{
	int r = row;
	int c = column;
	std::cout << "  ";
	for (size_t c = 1; c <= column; ++c) {
		std::cout << " - " << c ;
	}
	std::cout << std::endl;

	for (size_t r = 0; r < row; r++) {
		std::cout << " " << static_cast<char>('a' + r );
		for (size_t c = 1; c <= column + 1; ++c) {
			char board_char = ' ';
			for (const auto& coordinate : board) {
				if (std::get<0>(coordinate) == static_cast<char>('a' + r) && std::get<1>(coordinate) == c) {
					board_char = std::get<2>(coordinate);
					break;
				}
			}
			std::cout << " | " << board_char;
		}
		std::cout << std::endl;
		for (size_t c = 1; c <= column+1; ++c) {
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
	if (isValidCoor(chosenBox)) {
		markBox(chosenBox);
	} else {
		std::cout << "Not a valid coordinate, choose a legal target" << std::endl;
		chooseBox();
	};
}

void Gameboard::markBox(std::string& s) {
	std::pair<char, int> coor = parseCoordinates(s);

	for (auto& coordinate : board) {
		if (std::get<0>(coordinate) == coor.first && std::get<1>(coordinate) == coor.second) {
			std::get<2>(coordinate) = 'X';
			break;
		}
	}
}

int Gameboard::checkBoxes(std::string& s) {
	int amountOfMines = 0;
	/*if () {
	logic to check if adjacent boxes has mines or not
	};*/
	return amountOfMines;
}

bool Gameboard::isValidCoor(std::string& s) const {
		return
		s.size() == 2
		&& isalpha(s[0])
		&& isdigit(s[1])
		&& s[0] <= static_cast<char>('a' + row)
		&& (s[1] - '0') <= column;
}

std::pair<char, int> Gameboard::parseCoordinates(std::string& s) const{
	char char_coor = s[0];
	int int_coor = std::stoi(s.substr(1));
	return std::make_pair(char_coor, int_coor);
}

void Gameboard::randomizeMines() {
	char char_coor;
	int char_int;
	for (size_t i = row; i <= 0; i++) {

	}
};