#include "../headers/Operator.h"

#include <iostream>
Operator::Operator(const std::size_t _id, const std::string& _email, const std::string& _password, const std::string& _name): User(_id,_email,_password,"operator",_name){
}

Operator::~Operator(){

}