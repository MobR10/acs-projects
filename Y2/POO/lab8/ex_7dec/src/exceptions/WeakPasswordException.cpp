#include "../../headers/exceptions/WeakPasswordException.h"

WeakPasswordException::WeakPasswordException():
message("Password is weak! It must contain at least 1 symbol, 1 digit and 1 letter!\n"){}

const char* WeakPasswordException::what() const noexcept {
    return message.c_str();
}