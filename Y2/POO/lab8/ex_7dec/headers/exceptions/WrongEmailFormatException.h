#pragma once

#include <string>

class WrongEmailFormatException: public std::exception{

    std::string message;
    
    public:
    WrongEmailFormatException();
    virtual const char* what() const noexcept;
    
};