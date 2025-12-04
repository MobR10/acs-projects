#include "../../headers/exceptions/OperatorNotTripOwner.h"

OperatorNotTripOwner::OperatorNotTripOwner():
message("Operator is not the owner of this trip!\n"){}

const char* OperatorNotTripOwner::what() const noexcept {
    return message.c_str();
}