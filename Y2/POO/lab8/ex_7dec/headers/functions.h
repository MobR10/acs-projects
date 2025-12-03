#pragma once

#include <string>

void clearInput();

int isValidInput(const std::string& command,const std::string& sequence);

std::string readValue(const std::string& field);

void checkEmailFormat(const std::string& email);

int isValidDate(const std::string& date);

