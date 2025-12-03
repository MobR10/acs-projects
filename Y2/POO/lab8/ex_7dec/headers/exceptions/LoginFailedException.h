#pragma once

#include <string>

class LoginFailedException: public std::exception{

    std::string message;
    
    public:
    LoginFailedException();
    virtual const char* what() const noexcept;
    
};