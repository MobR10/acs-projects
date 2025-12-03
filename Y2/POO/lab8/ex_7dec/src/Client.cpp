#include "../headers/Client.h"
#include "../headers/Trip.h"

#include <iostream>
#include <string>

Client::Client(const std::string& _email, const std::string& _password, const std::string& _name): User(_email,_password,"client",_name){

}
