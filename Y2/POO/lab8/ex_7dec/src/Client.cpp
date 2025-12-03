#include "../headers/Client.h"
#include "../headers/Trip.h"

#include <iostream>
#include <string>

Client::Client(
    const std::size_t _id,
    const std::string& _email,
    const std::string& _password,
    const std::string& _name)
    :User(
        _id,
        _email,
        _password,
        "client",
        _name
    ){}

std::vector<std::shared_ptr<Trip>>& Client::getReservedTrips(){
    return reservedTrips;
}
