#pragma once

#include <string>

class WrongDateFormatException: public std::exception{

    std::string message;
    
    public:
    WrongDateFormatException();
    virtual const char* what() const noexcept;
    
};