#include "../headers/Client.h"

#include <iostream>
#include <string>

using namespace std;

Client::Client(const string& _email, const string& _password, const string& _name): User(_email,_password,"client",_name){
    
}
