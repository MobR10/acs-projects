#pragma once

#include <string>

class ShortPasswordException: public std::exception{

    std::string message;
    
    public:
    ShortPasswordException(int minLength);
    virtual const char* what() const noexcept;
    
};