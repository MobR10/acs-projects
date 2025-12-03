#include "../../headers/exceptions/NoTripException.h"

NoTripException::NoTripException():
message("The trip you entered doesn't exist!\n"){}

const char* NoTripException::what() const noexcept {
    return message.c_str();
}