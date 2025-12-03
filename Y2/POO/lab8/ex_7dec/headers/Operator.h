#pragma once

#include "User.h"
#include "Trip.h"

#include <string>
#include <memory>
#include <vector>

class Operator: public User{

    public:
    Operator(std::size_t id,const std::string& _email, const std::string& _password, const std::string& _name);
    ~Operator();

};