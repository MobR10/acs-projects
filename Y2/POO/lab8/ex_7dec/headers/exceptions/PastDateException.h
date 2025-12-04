#pragma once

#include <string>

class PastDateException: public std::exception{

    std::string message;
    
    public:
    PastDateException();
    virtual const char* what() const noexcept;
    
};