#pragma once

#include <string>

class OpenFileException: public std::exception{

    std::string message;
    
    public:
    OpenFileException(const std::string& _fileName);
    virtual const char* what() const noexcept;
    
};