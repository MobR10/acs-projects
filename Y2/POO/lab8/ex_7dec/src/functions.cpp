#include "../headers/functions.h"

#include <limits>
#include <iostream>
#include <string>
#include <ctime>
#include <format>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int isValidInput(const std::string& command,const std::string& sequence){
    if(command.length() != 1 || command.find_first_not_of(sequence) != std::string::npos)
        return 0;
    return 1;
}

std::string readValue(const std::string& field){
    std::cout<<"Enter "+ field + ": ";
    std::string line = "";
    getline(std::cin,line);

    std::cout<<"You entered " + field + ": " + line + "\n"; 
    return line;    
}

/// @brief 
/// @param date 
/// @return 1 if the date is in a correct format and chronological order
/// 
/// 0  (wrong format) 
///
/// -1 (chronologically incorrect)  
int isValidDate(const std::string& date){
    // dd/mm/yyyy
    if(date.size() != 10)
        return 0;
    
    if(date.find_first_of("/") != 2 || date.find_last_of("/") != 5)
        return 0;

    
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    char buffer[5];

    // Year
    std::sprintf(buffer, "%04d", now->tm_year + 1900);
    std::string year = buffer;

    // Month
    std::sprintf(buffer, "%02d", now->tm_mon + 1);
    std::string month = buffer;

    // Day
    std::sprintf(buffer, "%02d", now->tm_mday);
    std::string day = buffer;

    if(date.substr(6) < year)
        return -1;
    
    if(date.substr(3,4) < month)
        return -1;
    
    if(date.substr(0,1) < day)
        return -1;

    return 1;
}

