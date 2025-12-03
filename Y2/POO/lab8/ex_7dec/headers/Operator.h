#pragma once

#include "User.h"
#include "Trip.h"

#include <string>
#include <vector>

using namespace std;

class Operator: public User{
    std::vector<Trip> trips;

    public:
    Operator(const string& _email, const string& _password, const string& _name);
    ~Operator();

};