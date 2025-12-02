#pragma once

#include "User.h"

#include <string>

using namespace std;

class Operator: public User{
        
    public:
    Operator(const string& _email, const string& _password, const string& _name);
    ~Operator();


};