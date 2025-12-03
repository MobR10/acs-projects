#include "../../headers/exceptions/ReadUsersException.h"

ReadUsersException::ReadUsersException(const int& userIndex):
message("Something happened at reading users! Check the csv file at the " +
             std::to_string(userIndex) + "th user."){}

const char* ReadUsersException::what() const noexcept {
    return message.c_str();
}