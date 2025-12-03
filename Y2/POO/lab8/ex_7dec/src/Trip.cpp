#include "../headers/Trip.h"
#include "../headers/Manager.h"

#include <string>
#include <iostream>
    
    Trip::Trip(std::size_t _id,
        std::size_t _operatorId,
        const std::string& _name,
        const std::string& _city,
        const std::string& _date):
    id(_id), operatorId(_operatorId), name(_name), city(_city), date(_date) {}


std::size_t Trip::getId() const {
    return id;
}

std::size_t Trip::getOperatorId() const {
    return operatorId;
}

const std::string& Trip::getName() const {
    return name;
}

const std::string& Trip::getCity() const {
    return city;
}

const std::string& Trip::getDate() const {
    return date;
}

void Trip::printInfo(Manager& manager){
    std::cout<<"Trip ID = " + std::to_string(id) + "\n";
    std::cout<<"Operator's name: " + manager.getOperatorName(operatorId) + "\n";
    std::cout<<"City: " + city + "\n";
    std::cout<<"Date: " + date + "\n================\n";
}
