#include "FileManagement.h"
#include <iostream>

FileManagement::FileManagement(const std::string& filename) {
    file.open(filename, std::ios::out | std::ios::app);
    infile.open(filename, std::ios::in);
}

FileManagement::~FileManagement() {
    if (file.is_open()) {
        file.close();
    }
    if (infile.is_open()) {
        infile.close();
    }
}

void FileManagement::write(const std::string& text) {
    if (file.is_open()) {
        file << text << std::endl;
    }
    else {
        std::cout << "File is not open" << std::endl;
    }
}

std::istringstream FileManagement::read() {
    std::string content;
    std::string line;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            content += line + "\n";
        }
    }
    else {
        std::cout << "File is not open" << std::endl;
    }
    return std::istringstream(content);
}