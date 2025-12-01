#ifndef OPENFILEEXCEPTION_H

#define OPENFILEEXCEPTION_H

#include <string>

using namespace std;

class OpenFileException: public exception{

    string message;
    
    public:
    OpenFileException(const string& _fileName);
    virtual const char* what() const noexcept;
    
};

#endif