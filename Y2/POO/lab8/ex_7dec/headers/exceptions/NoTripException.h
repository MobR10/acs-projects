#pragma once

#include <string>

class NoTripException: public std::exception{

    std::string message;
    
    public:
    NoTripException();
    virtual const char* what() const noexcept;
    
};