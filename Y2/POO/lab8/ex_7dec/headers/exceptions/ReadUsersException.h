#ifndef READUSERSEXCEPTION_H

#define READUSERSEXCEPTION_H

#include <string>

using namespace std;

class ReadUsersException: public exception{

    string message;
    
    public:
    ReadUsersException(const int& userIndex);
    virtual const char* what() const noexcept;
    
};

#endif