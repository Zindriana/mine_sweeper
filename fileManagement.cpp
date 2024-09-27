#include "FileManagement.h"
#include <iostream>

//Constructor
FileManagement::FileManagement(const std::string& filename) {
    file.open(filename, std::ios::out | std::ios::app);
    infile.open(filename, std::ios::in);
}

//Destructor
FileManagement::~FileManagement() {
    if (file.is_open()) {
        file.close();
    }
    if (infile.is_open()) {
        infile.close();
    }
}

//Saving the gameboard happens in the gameboard class right now, would be nice to have all filemanagement in the same class
    //void filemanagement::write(const std::string& text) {
    //    if (file.is_open()) {
    //        file << text << std::endl;
    //    }
    //    else {
    //        std::cout << "file is not open" << std::endl;
    //    }
    //}

//Getting the info from a txt.file 
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