#include "../../headers/exceptions/LoginFailedException.h"

LoginFailedException::LoginFailedException():
message("Email or password are wrong!\n"){}

const char* LoginFailedException::what() const noexcept {
    return message.c_str();
}