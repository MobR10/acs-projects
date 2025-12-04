#pragma once

#include <string>

class OperatorNotTripOwner: public std::exception{

    std::string message;

    public:
    OperatorNotTripOwner();
    virtual const char* what() const noexcept;
};