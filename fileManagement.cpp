#include "FileManagement.h"
#include <iostream>

FileManagement::FileManagement(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Couldn´t open file" << std::endl;
    }
}

FileManagement::~FileManagement() {
    if (file.is_open()) {
        file.close();
    }
}

void FileManagement::write(const std::string& text) {
    if (file.is_open()) {
        file << text << std::endl;
    }
    else {
        std::cerr << "File is not open" << std::endl;
    }
}