#pragma once
#include <string>
#include <fstream>
#include <sstream>

class FileManagement {
public:
    FileManagement(const std::string& filename);
    ~FileManagement();
    void write(const std::string& text);
    std::istringstream read();

private:
    std::ofstream file;
    std::ifstream infile;
};