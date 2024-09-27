#pragma once
#include <string>
#include <fstream>
#include <sstream>

class FileManagement {
private:
    std::ofstream file;
    std::ifstream infile;

public:
    FileManagement(const std::string& filename);
    ~FileManagement();
    //void write(const std::string& text); this methos isn´t used in the moment, method saveBoard in gameboard class is used insted
    std::istringstream read();

};