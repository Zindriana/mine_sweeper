#include "gameboard.h"
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include "input.h"
#include <fstream>

//Constructor
Gameboard::Gameboard(const int row, const int column, const Input* input) : row(row), column(column), input(input) {
	for (char r = 'a'; r < 'a' + row; ++r) { //preincrement is more effective, because postincrement needs to creata a copy first
		for (size_t c = 1; c <= column; ++c) {
			board.push_back(std::make_tuple(r, c, starting_char, mine));
			//call for randomizeMines() here instead of in the main class
			//didn´t move randomizeMines() to this place, because it would probably create bugs when loading an existing file
		}
	}
}

//Method that saves the current state of the board to a .txt-file.
//This method can probably stay here in this class for now, but it would be nice to have it in fileManagement class instead
void Gameboard::saveBoard(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cout << "Could not open file for writing!" << std::endl;
		return;
	}

	file << row << " " << column << std::endl;
	for (const auto& cell : board) {
		file << std::get<0>(cell) << " "
			<< std::get<1>(cell) << " "
			<< std::get<2>(cell) << " "
			<< std::get<3>(cell) << std::endl;
	}
	std::cout << "Game board is saved \n" << std::endl;
	file.close();
}

//This method renders the gameboard in the terminal 
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
				if (std::get<0>(coor) == 'a' + r && std::get<1>(coor) == c) {
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

//This method controls if a cell contains a mine or not. If it contains a mine, it returns true and the game is over
//If false, then the method first calls checkCells() and eventually also expandZeroes()
bool Gameboard::exploreCell(const std::string& s) {
	std::pair<char, int> coordinate = input->parseCoordinates(s);

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
			int amountOfMines = checkCells(s);
			std::get<2>(coor) = '0' + amountOfMines;
			if (amountOfMines == 0) {
				expandZeroes(s);
			}
			return false;
		}
	}
}

//Method that mark a cell as flagged (changing the cells graphic to an 'F')
void Gameboard::flagCell(const std::string& s) {
	std::pair<char, int> coordinate = input->parseCoordinates(s);
	for (auto& coor : board) {
		if (std::get<0>(coor) == coordinate.first
			&& std::get<1>(coor) == coordinate.second) {
			if (std::get<2>(coor) == '?') {
				std::get<2>(coor) = 'F';
			}
			else {
				std::cout << "The target area is already explored, choose a new area. " << std::endl;
			}			
		}
	}
}

//This method is called from exploreCell(), it loop through all adjacent cells to check how many mines that are adjacent to the explored cell
int Gameboard::checkCells(const std::string& s) {
	int amountOfMines = 0;
	std::pair<char, int> coordinate = input->parseCoordinates(s);
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			char char_coor = coordinate.first + i;
			int int_coor = coordinate.second + j;
			if (input->isValidCoor(s) && !(i == 0 && j == 0)) {
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

//This method is called when the player explore a cell that neither contains a mine nor has any adjacent mines,
//it then loops through all adjacent nonexplored nonflagged cells and call the exploreCell()
void Gameboard::expandZeroes(const std::string& s) {
	std::pair<char, int> coordinate = input->parseCoordinates(s);
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			char char_coor = coordinate.first + i;
			int int_coor = coordinate.second + j;
			if (input->isValidCoor(s) && !(i == 0 && j == 0)) {
				for (auto& coor : board) {
					if (std::get<0>(coor) == char_coor
						&& std::get<1>(coor) == int_coor
						&& std::get<2>(coor) == '?') { //'?' = nonexplored nonflagged cell
						std::string newS;
						newS += static_cast<char>(coordinate.first + i);
						newS += std::to_string(coordinate.second + j);
						exploreCell(newS);
					}
				}
			}
		}
	}
}

//Method that adds and randomizes mine placements when creating a new gameboard
void Gameboard::randomizeMines(const int startingMines) {
	char char_coor;
	int char_int;
	for (size_t i = 0; i <= startingMines; ++i) {
		char_coor = 'a' + std::rand() % row;
		char_int = 1 + std::rand() % column;
		for (auto& coor : board) {
			if (std::get<0>(coor) == char_coor && std::get<1>(coor) == char_int && std::get<3>(coor) == false ) {//get<3> == false was added to avoid that a mine is placed where there already exists a mine
				std::get<3>(coor) = true;
				break;
			}
		}
	}
}

bool Gameboard::checkForVictory() {
	bool marked = true;
	for (auto& coor : board) {
		if(std::get<2>(coor) == '?' && std::get<3>(coor) == false) {
			marked = false;
		}
	}
	return marked;
}

//This method can probably stay here, maybe could have been moved to the fileManagement class
void Gameboard::setCell(const int r, const int c, const char value, const bool isMine) { //r = row, c=column, value= symbol that is displayd on the board
	for (auto& cell : board) {
		if (std::get<0>(cell) == r && std::get<1>(cell) == c) {
			std::get<2>(cell) = value;
			std::get<3>(cell) = isMine;
			break;
		}
	}
}
