#pragma once

#include <string>

class Trip{
    std::string name,location;
    int space, days;
    
    public:
    Trip(const std::string& _name, const std::string& _location, int days,int space);
    
};