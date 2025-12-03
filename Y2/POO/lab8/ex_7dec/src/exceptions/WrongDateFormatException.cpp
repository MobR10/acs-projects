#include "../../headers/exceptions/WrongDateFormatException.h"

WrongDateFormatException::WrongDateFormatException():
message("Date format is wrong! It should be dd/mm/yyyy\n"){}

const char* WrongDateFormatException::what() const noexcept {
    return message.c_str();
}