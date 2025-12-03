#pragma once


#include <string>

class Manager;

class Trip{

    std::size_t id, operatorId;
    std::string name,city,date;
    
    public:
    Trip(std::size_t _id,
        std::size_t operatorId,
        const std::string& _name,
        const std::string& _city,
        const std::string& _date);

    std::size_t getId() const;
    std::size_t getOperatorId() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    const std::string& getDate() const;

    void printInfo(Manager& manager);
};