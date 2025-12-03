#include "../../headers/exceptions/InvalidTripIdException.h"

InvalidTripIdException::InvalidTripIdException():
message("The trip with the ID you specified doesn't exist!\n"){}

const char* InvalidTripIdException::what() const noexcept {
    return message.c_str();
}