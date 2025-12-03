#pragma once

#include "User.h"
#include "Trip.h"
#include <memory>
#include <string>
#include <vector>

class Trip;

class Client: public User{
    std::vector<std::shared_ptr<Trip>> reservedTrips;
    
    public:
    Client(std::size_t id,const std::string& _email, const std::string& _password, const std::string& _name);

    std::vector<std::shared_ptr<Trip>>& getReservedTrips();
};