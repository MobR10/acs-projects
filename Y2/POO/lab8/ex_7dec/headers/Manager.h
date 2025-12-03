#pragma once

#include "User.h"
#include "Client.h"
#include "Operator.h"

#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Manager{
    ifstream f;
    size_t usersN;
    vector<std::unique_ptr<User>> users;
    

    void readUsers();
    void findUsersN();
    string readString(string& line);

    public:
        Manager(const string& _fileName);

        ~Manager();

        User* login(const string& email, const string& password);

        void logout(User*& user, int& userLoggedIn);

};