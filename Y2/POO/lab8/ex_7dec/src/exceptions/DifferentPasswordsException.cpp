#include "../../headers/exceptions/DifferentPasswordsException.h"

DifferentPasswordsException::DifferentPasswordsException():
message("Passwords don't match!\n"){}

const char* DifferentPasswordsException::what() const noexcept {
    return message.c_str();
}