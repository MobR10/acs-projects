#include "../../headers/exceptions/ReadUsersException.h"

#include <iostream>
#include <string>

using namespace std;

ReadUsersException::ReadUsersException(const int& userIndex):
message("Something happened at reading users! Check the csv file at the " +
             to_string(userIndex) + "th user."){}

const char* ReadUsersException::what() const noexcept {
    return message.c_str();
}