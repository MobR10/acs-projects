#include "../../headers/exceptions/WrongEmailFormatException.h"

WrongEmailFormatException::WrongEmailFormatException():
message("Wrong email format!\n"){}

const char* WrongEmailFormatException::what() const noexcept {
    return message.c_str();
}