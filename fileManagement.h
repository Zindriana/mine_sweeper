#pragma once
#include <string>
#include <fstream>
#include <sstream>

class FileManagement {
public:
    FileManagement(const std::string& filename);
    ~FileManagement();
    //void write(const std::string& text); this methos isn´t used in the moment, method saveBoard in gameboard class is used insted
    std::istringstream read();

private:
    std::ofstream file;
    std::ifstream infile;
};