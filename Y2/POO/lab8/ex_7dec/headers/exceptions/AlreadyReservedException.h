#pragma once

#include <string>

class AlreadyReservedException: public std::exception{

    std::string message;
    
    public:
    AlreadyReservedException();
    virtual const char* what() const noexcept;
    
};