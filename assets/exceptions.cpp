//
// Created by Seth Riddensdale on 4/22/24.
//

#include "exceptions.h"

// FileNotFound exception constructor
FileNotFound::FileNotFound(string filePath){
    this->filePath = filePath;
}

// Getter for the file path string
string FileNotFound::getFilePath() const{
    return filePath;
}
