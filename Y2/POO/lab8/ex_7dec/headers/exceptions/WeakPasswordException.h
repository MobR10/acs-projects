#pragma once

#include <string>

class WeakPasswordException: public std::exception{

    std::string message;
    
    public:
    WeakPasswordException();
    virtual const char* what() const noexcept;
    
};