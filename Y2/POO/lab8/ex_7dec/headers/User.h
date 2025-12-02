#pragma once

#include <string>
using namespace std;
class User{

    protected:
    string email;
    string password;
    string role;
    string name;

    public:
    User(const string& _email, const string& _password, const string& _role, const string& _name);
    virtual ~User();
};