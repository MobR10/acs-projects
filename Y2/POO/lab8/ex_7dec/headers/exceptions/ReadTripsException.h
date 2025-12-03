#pragma once

#include <string>

class ReadTripsException: public std::exception{

    std::string message;
    
    public:
    ReadTripsException(const int& userIndex);
    virtual const char* what() const noexcept;
    
};