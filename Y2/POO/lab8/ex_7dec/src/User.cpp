#include "../headers/User.h"

#include <iostream>
#include <string>

using namespace std;

User::User(const string& _email, const string& _password, const string& _role, const string& _name):
    email(_email),password(_password),role(_role),name(_name){}

User::~User(){}