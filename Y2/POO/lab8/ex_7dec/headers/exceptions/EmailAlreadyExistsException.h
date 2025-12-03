#pragma once

#include <string>

class EmailAlreadyExistsException: public std::exception{
    std::string message;

    public:
        EmailAlreadyExistsException();
        virtual const char* what() const noexcept;
    
};