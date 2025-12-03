#include "../headers/User.h"

#include <iostream>
#include <string>

User::User(std::size_t _id,const std::string& _email, const std::string& _password, const std::string& _role, const std::string& _name):
    id(_id), email(_email), password(_password), role(_role), name(_name){}

User::~User(){}

std::size_t User::getId() const{
    return this->id;
}

const std::string User::getEmail() const{
    return email;
}

const std::string User::getPassword() const{
    return password;
}
const std::string User::getRole() const{
    return role;
}
const std::string User::getName() const{
    return name;
}

