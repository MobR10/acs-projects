#pragma once

#include <string>

using namespace std;

class OpenFileException: public exception{

    string message;
    
    public:
    OpenFileException(const string& _fileName);
    virtual const char* what() const noexcept;
    
};