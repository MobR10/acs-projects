#include "../headers/User.h"

#include <iostream>
#include <string>

using namespace std;

User::User(const string& _email, const string& _password, const string& _role, const string& _name):
    email(_email),password(_password),role(_role),name(_name){}

User::~User(){}

std::string User::getEmail() const{
    return this->email;
}

std::string User::getPassword() const{
    return this->password;
}
std::string User::getRole() const{
    return this->role;
}
std::string User::getName() const{
    return this->name;
}

