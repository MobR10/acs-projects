#include "../../headers/exceptions/AlreadyReservedException.h"

AlreadyReservedException::AlreadyReservedException():
message("This trip is already reserved!\n"){}

const char* AlreadyReservedException::what() const noexcept {
    return message.c_str();
}