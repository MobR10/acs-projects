#pragma once

#include <string>

class InvalidTripIdException: public std::exception{
    std::string message;

    public:
        InvalidTripIdException();
        virtual const char* what() const noexcept;
    
};