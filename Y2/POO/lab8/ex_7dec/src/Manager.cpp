#include "../headers/Manager.h"
#include "../headers/exceptions/OpenFileException.h"
#include "../headers/exceptions/ReadUsersException.h"

#include "../headers/functions.h"

#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>

constexpr auto BEGIN = std::ios::beg;
constexpr auto CURRENT = std::ios::cur;
constexpr auto END = std::ios::end;

Manager::Manager(const string& _fileName) {
    string fileName = _fileName;

    while (true) {
        try{
            try {
                f.open(fileName);
                if (!f.is_open()) {
                    throw OpenFileException(fileName);
                }
                }catch(const OpenFileException& e){
                cout<<e.what()<<endl;
                throw;
                }

                cout << "Se incarca utilizatorii din fisierul \"" << fileName << "\"...\n";
                findUsersN();

                try{
                    readUsers();
                }catch(const ReadUsersException& e){
                    cout<<e.what()<<endl;
                    throw;
                }

                break;  //exit loop
        }catch(...){
            cout << "Point me to another file or write N to terminate the execution: ";
            string command;
            cin >> command;
            clearInput();

            if (command == "N" || command == "n") {
                cout<<"Terminating the program...";
                exit(0);
            } else {
                fileName = command; // try new file
                f.close();          // close previous file before retry
            }
        }
    }
    cout << "Utilizatorii au fost incarcati cu succes!\n";
}


Manager::~Manager(){
    // Memory frees itself through vector and unique_ptr
    if(f.is_open())
        f.close();
}

void Manager::findUsersN(){
    f.clear();
    f.seekg(0,BEGIN);

    string line= "";
    usersN = 0;

    getline(f,line);

    while(getline(f,line)){
        usersN++;
    }
}

string Manager::readString(string& line){
    size_t comma = line.find(',');
    string field = line.substr(0,comma);
    line = line.substr(comma+1);

    return field;
}

void Manager::readUsers(){

    f.clear();
    f.seekg(0,BEGIN);

    string line= "";
    getline(f,line);

    size_t usersIndex= 0;
    
    while(getline(f,line)){

        // GET EMAIL
        const string email = readString(line);

        // GET PASSWORD
        const string password = readString(line);

        // GET ROLE
        const string role = readString(line);
        
        // GET NAME
        const string name = readString(line);

        if(role == "client"){
            users.push_back(std::make_unique<Client>(email,password,name));
            usersIndex++;
        }
        else if(role == "operator"){
            users.push_back(std::make_unique<Operator>(email,password,name));
            usersIndex++;
        }
        else{
            throw ReadUsersException(static_cast<int>(usersIndex));
        }
    }
}

User* Manager::login(const string& email, const string& password){
    for(std::unique_ptr<User>& x: users){
        if(x->getEmail() == email && x->getPassword()== password){
            return x.get();
        }
    }
    return nullptr;
}

void Manager::logout(User*& user,int& userLoggedIn){
    user = nullptr;
    userLoggedIn = 0;
}