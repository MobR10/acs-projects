#include "../../headers/exceptions/ReadTripsException.h"

ReadTripsException::ReadTripsException(const int& tripIndex):
message("Something happened at reading TRIPS! Check the csv file at the " +
             std::to_string(tripIndex) + "th trip."){}

const char* ReadTripsException::what() const noexcept {
    return message.c_str();
}