#include "../../headers/exceptions/ShortPasswordException.h"

ShortPasswordException::ShortPasswordException(int minLength):
message("Password must be at least "+ std::to_string(minLength) + " characters long!\n"){}

const char* ShortPasswordException::what() const noexcept {
    return message.c_str();
}