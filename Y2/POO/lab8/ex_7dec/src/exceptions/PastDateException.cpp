#include "../../headers/exceptions/PastDateException.h"

PastDateException::PastDateException():
message("Date is in the past!\n"){}

const char* PastDateException::what() const noexcept {
    return message.c_str();
}