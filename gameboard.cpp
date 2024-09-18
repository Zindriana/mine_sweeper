#include "gameboard.h"
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <cctype>
#include "mine.h"
#include <ctime>
#include <cstdlib>

Gameboard::Gameboard(int row, int column) : row(row), column(column) {
	for (char r = 'a'; r <= 'a' + row; ++r) { //preincrement �r effektivare
		for (size_t c = 1; c <= column; ++c) { //postincrement beh�ver skapa en kopia f�rst
			board.push_back(std::make_tuple(r, c, starting_char, mine));
		}
	}
}

void Gameboard::render() const{
	std::cout << "  ";
	for (size_t c = 1; c <= column; ++c) {
		std::cout << " - " << c ;
	}
	std::cout << std::endl;

	for (size_t r = 0; r < row; r++) {
		std::cout << " " << static_cast<char>('a' + r );
		for (size_t c = 1; c <= column + 1; ++c) {
			char board_char = ' ';
			for (const auto& coor : board) {
				if (std::get<0>(coor) == static_cast<char>('a' + r) && std::get<1>(coor) == c) {
					board_char = std::get<2>(coor);
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

bool Gameboard::chooseBox(char c) {
	bool kaboom = false;
	std::string chosenBox = "";
	std::cout << "which box do you want to mark?" << std::endl;
	std::cin >> chosenBox;
	if (isValidCoor(chosenBox) && c == 'e') {
		kaboom = exploreBox(chosenBox);
	} else if (isValidCoor(chosenBox) && c == 'f') {
		flagBox(chosenBox);
	} else {
		std::cout << "Not a valid coordinate, choose a legal target" << std::endl;
		chooseBox(c);
	};
	return kaboom;
}

bool Gameboard::exploreBox(std::string& s) {
	std::pair<char, int> coordinate = parseCoordinates(s);

	for (auto& coor : board) {
		if (std::get<0>(coor) == coordinate.first
			&& std::get<1>(coor) == coordinate.second
			&& std::get<3>(coor) == true) {
			std::get<2>(coor) = 'M';
			return true;
		}
		else if (std::get<0>(coor) == coordinate.first
			&& std::get<1>(coor) == coordinate.second
			&& std::get<3>(coor) == false){
			int amountOfMines = checkBoxes(s);
			std::get<2>(coor) = '0' + amountOfMines;
			return false;
		}
	}
}

void Gameboard::flagBox(std::string& s) {
	std::pair<char, int> coordinate = parseCoordinates(s);
	for (auto& coor : board) {
		if (std::get<0>(coor) == coordinate.first
			&& std::get<1>(coor) == coordinate.second) {
			if (std::get<2>(coor) == ' ') {
				std::get<2>(coor) = 'F';
			}
			else {
				std::cout << "The target area is already explored, choose a new area. " << std::endl;
			}			
		}
	}
}

int Gameboard::checkBoxes(std::string& s) {
	int amountOfMines = 0;
	std::pair<char, int> coordinate = parseCoordinates(s);
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			char char_coor = coordinate.first + i;
			int int_coor = coordinate.second + j;
			if (char_coor >= 'a' && char_coor <= 'a' + row -1 && int_coor > 0 && int_coor <= column && !(i == 0 && j == 0)) {
				for (auto& coor : board) {
					if (std::get<0>(coor) == char_coor
						&& std::get<1>(coor) == int_coor
						&& std::get<3>(coor) == true) {
						++amountOfMines;
					}
				}
			}
		}
	}
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
	for (size_t i = 0; i <= row; ++i) {
		char_coor = 'a' + std::rand() % row;
		char_int = 1 + std::rand() % column;
		for (auto& coor : board) {
			if (std::get<0>(coor) == char_coor && std::get<1>(coor) == char_int) {
				std::get<3>(coor) = true;
				break;
			}
		}
	}
}