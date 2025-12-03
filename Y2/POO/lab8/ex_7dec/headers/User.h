#pragma once

#include <string>

class User{

    protected:
    std::string email;
    std::string password;
    std::string role;
    std::string name;

    public:
    User(const std::string& _email, const std::string& _password, const std::string& _role, const std::string& _name);
    virtual ~User();

    std::string getEmail() const;
    std::string getPassword() const;
    std::string getRole() const;
    std::string getName() const;
    
};