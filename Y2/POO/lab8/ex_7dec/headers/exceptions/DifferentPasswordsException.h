#pragma once

#include <string>

class DifferentPasswordsException: public std::exception{

    std::string message;
    
    public:
    DifferentPasswordsException();
    virtual const char* what() const noexcept;
    
};