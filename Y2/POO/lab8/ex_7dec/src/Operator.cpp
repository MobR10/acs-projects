#include "../headers/Operator.h"

#include <iostream>
Operator::Operator(const string& _email, const string& _password, const string& _name): User(_email,_password,"operator",_name){
    
}

Operator::~Operator(){

}