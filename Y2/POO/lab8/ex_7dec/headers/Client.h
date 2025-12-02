#pragma once

#include "User.h"
#include <string>

using namespace std;

class Client: public User{
    
    public:
    Client(const string& _email, const string& _password, const string& _name);
};