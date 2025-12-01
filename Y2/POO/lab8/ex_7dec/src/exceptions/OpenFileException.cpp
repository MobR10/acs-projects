#include "../../headers/exceptions/OpenFileException.h"

#include <iostream>
#include <string>

using namespace std;

OpenFileException::OpenFileException(const string& _fileName):
message("I ran into an issue when trying to open the file \""+_fileName+"\"...\n"){}

const char* OpenFileException::what() const noexcept {
    return message.c_str();
}