#pragma once

#include "User.h"
#include "Trip.h"
#include <string>
#include <vector>

class Trip;

class Client: public User{
    std::vector<Trip> reservedTrips;
    
    public:
    Client(const std::string& _email, const std::string& _password, const std::string& _name);
};