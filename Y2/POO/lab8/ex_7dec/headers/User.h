#pragma once

#include <string>

class User{

    protected:
    std::size_t id;
    std::string email;
    std::string password;
    std::string role;
    std::string name;

    public:
    User(std::size_t id,const std::string& _email, const std::string& _password, const std::string& _role, const std::string& _name);
    virtual ~User();

    std::size_t getId() const;
    const std::string getEmail() const;
    const std::string getPassword() const;
    const std::string getRole() const;
    const std::string getName() const;
    
};