#pragma once

#include <string>

using namespace std;

class ReadUsersException: public exception{

    string message;
    
    public:
    ReadUsersException(const int& userIndex);
    virtual const char* what() const noexcept;
    
};