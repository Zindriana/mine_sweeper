#pragma once
#include <string>
#include <fstream>

class FileManagement {
public:
    FileManagement(const std::string& filename);
    ~FileManagement();
    void write(const std::string& text);

private:
    std::ofstream file;
};

