#include "../headers/functions.h"

#include <limits>
#include <iostream>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int isValidInput(const std::string& command,const std::string& sequence){
    if(command.length() != 1 || command.find_first_not_of(sequence) != std::string::npos)
        return 0;
    return 1;
}