//
// Created by Seth Riddensdale on 4/22/24.
//

#ifndef MYPROJECT_EXCEPTIONS_H
#define MYPROJECT_EXCEPTIONS_H
#include <string>

using namespace std;

class FileNotFound {
private:
    string filePath;

public:
    FileNotFound(string filePath);
    string getFilePath() const;
};


#endif //MYPROJECT_EXCEPTIONS_H
