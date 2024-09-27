#include "input.h"

Input::Input(int row, int column) : row(row), column(column) {

}

//Method that checks that the coordinate is within the gameboard limits
bool Input::isValidCoor(const std::string& s) const{
	std::pair<char, int> coordinate = parseCoordinates(s);
	return coordinate.first >= 'a'
		&& coordinate.first <= 'a' + row - 1
		&& coordinate.second > 0
		&& coordinate.second <= column;
}

//Method that checks that the player input is a valid format for a coordinate
std::pair<char, int> Input::parseCoordinates(const std::string& s) const{
	char char_coor = s[0];
	int int_coor = -1;
	try {
		int_coor = std::stoi(s.substr(1));
	}
	catch (const std::invalid_argument& e) {
		return std::make_pair(char_coor, -1);
	}
	return std::make_pair(char_coor, int_coor);
}

void Input::setRow(int r) {
	row = r;
}

void Input::setColumn(int c) {
	column = c;
}