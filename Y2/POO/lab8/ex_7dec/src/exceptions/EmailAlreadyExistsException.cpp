#include "../../headers/exceptions/EmailAlreadyExistsException.h"

EmailAlreadyExistsException::EmailAlreadyExistsException():
message("Email already exists!\n"){}

const char* EmailAlreadyExistsException::what() const noexcept {
    return message.c_str();
}