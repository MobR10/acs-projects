#ifndef MANAGER_H

#define MANAGER_H

#include "User.h"
#include "Client.h"
#include "Operator.h"

#include <fstream>
#include <string>

using namespace std;

class Manager{
    ifstream f;
    size_t usersN;
    User **users;

    void readUsers();
    void findUsersN();
    string readString(string& line);

    public:
        Manager(const string& _fileName);

        ~Manager();

        int login(const string& email, const string& password);
};

#endif