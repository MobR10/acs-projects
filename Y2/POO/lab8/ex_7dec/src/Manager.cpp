#include "../headers/Manager.h"
#include "../headers/functions.h"

// exceptions
#include "../headers/exceptions/OpenFileException.h"
#include "../headers/exceptions/ReadUsersException.h"
#include "../headers/exceptions/ReadTripsException.h"
#include "../headers/exceptions/WeakPasswordException.h"
#include "../headers/exceptions/ShortPasswordException.h"
#include "../headers/exceptions/DifferentPasswordsException.h"
#include "../headers/exceptions/WrongEmailFormatException.h"
#include "../headers/exceptions/EmailAlreadyExistsException.h"
#include "../headers/exceptions/InvalidTripIdException.h"
#include "../headers/exceptions/WrongDateFormatException.h"
#include "../headers/exceptions/PastDateException.h"
#include "../headers/exceptions/AlreadyReservedException.h"
#include "../headers/exceptions/OperatorNotTripOwner.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm>

constexpr auto BEGIN = std::ios::beg;
constexpr auto CURRENT = std::ios::cur;
constexpr auto END = std::ios::end;

Manager::Manager(const std::string& _usersFileName,const std::string& _tripsFileName, const std::string& _mapFileName):
usersFileName(_usersFileName), tripsFileName(_tripsFileName), mapFileName(_mapFileName)
{

    // LOAD TRIPS FILE
    while(true){
        try{
            try {
                tripsFile.open(tripsFileName, std::ios::in | std::ios::out);
                if (!tripsFile.is_open()) {
                    throw OpenFileException(tripsFileName);
                }
                }catch(const OpenFileException& e){
                std::cout<<e.what()<<std::endl;
                throw;
                }

                std::cout << "Se incarca utilizatorii din fisierul \"" << tripsFileName << "\"...\n";
                // findTripsN(); deprecated

                try{
                    readTrips();
                }catch(const ReadTripsException& e){
                    std::cout<<e.what()<<std::endl;
                    throw;
                }
            }catch(...){
                std::cout << "Point me to another file or write N to terminate the execution: ";
                std::string command;
                std::cin >> command;
                clearInput();

                if (command == "N" || command == "n") {
                    std::cout<<"Terminating the program...";
                    exit(0);
                } else {
                    tripsFileName = command;    // try new file
                    tripsFile.close();  // close previous file before retry
                }
            }
        break;   
    }
    
    // LOAD USERS
    while(true){
        try{
            try {
                usersFile.open(usersFileName, std::ios::in | std::ios::out);
                if (!usersFile.is_open()) {
                    throw OpenFileException(usersFileName);
                }
                }catch(const OpenFileException& e){
                std::cout<<e.what()<<std::endl;
                throw;
                }

                std::cout << "Se incarca utilizatorii din fisierul \"" << usersFileName << "\"...\n";
                // findUsersN(); deprecated

                try{
                    readUsers();
                }catch(const ReadUsersException& e){
                    std::cout<<e.what()<<std::endl;
                    throw;
                }
            }catch(...){
                std::cout << "Point me to another file or write N to terminate the execution: ";
                std::string command;
                std::cin >> command;
                clearInput();

                if (command == "N" || command == "n") {
                    std::cout<<"Terminating the program...";
                    exit(0);
                } else {
                    usersFileName = command; // try new file
                    usersFile.close();          // close previous file before retry
                }
            }
        break;
    }

    while(true){
        try{
            try{
                mapFile.open(mapFileName, std::ios::in | std::ios::out );
                if(!mapFile.is_open())
                    throw OpenFileException(mapFileName);
            }catch(const OpenFileException& e){
                    std::cout<<e.what();
            }

            std::cout << "Se incarca utilizatorii din fisierul \"" << mapFileName << "\"...\n";

            readMap();

        }catch(...){
            std::cout << "Point me to another file or write N to terminate the execution: ";
            std::string command;
            std::cin >> command;
            clearInput();

            if (command == "N" || command == "n") {
                std::cout<<"Terminating the program...";
                exit(0);
            } else {
                mapFileName = command;    // try new file
                mapFile.close();  // close previous file before retry
            }
        }
        break;
    }

    std::cout << "Fisierele au fost incarcate cu succes!\n";
}




Manager::~Manager(){
    // Memory frees itself through vector and unique_ptr
    if(usersFile.is_open())
        usersFile.close();
    if(tripsFile.is_open())
        tripsFile.close();
    if(mapFile.is_open())
        mapFile.close();
}

std::string Manager::readString(std::string& line){
    std::size_t comma = line.find(',');
    std::string field = line.substr(0,comma);
    line = line.substr(comma+1);

    return field;
}

void Manager::readTrips(){

    trips.clear();

    tripsFile.clear();
    tripsFile.seekg(0,BEGIN);

    std::string line= "";
    std::getline(tripsFile,line);

    tripsN = 0;
    
    while(std::getline(tripsFile,line)){
        // id,operatorId,name,city,date

        // GET id
        const std::string id = readString(line);
        tripIds.push_back(stoi(id));

        // GET operatorID 
        const std::string operatorId = readString(line);
        
        // GET Name
        const std::string name = readString(line);

        // GET PASSWORD
        const std::string city = readString(line);

        // GET ROLE
        const std::string date = readString(line);
        
        trips.push_back(std::make_shared<Trip>(stoi(id),stoi(operatorId),name,city,date));
    }
}


void Manager::readUsers(){

    users.clear();

    usersFile.clear();
    usersFile.seekg(0,BEGIN);

    std::string line= "";
    std::getline(usersFile,line);

    usersN = 0;
    
    while(std::getline(usersFile,line)){

        // GET ID
        const std::string id = readString(line);
        userIds.push_back(stoi(id));

        // GET EMAIL
        const std::string email = readString(line);

        // GET PASSWORD
        const std::string password = readString(line);

        // GET ROLE
        const std::string role = readString(line);
        
        // GET NAME
        const std::string name = readString(line);

        if(role == "client"){
            users.push_back(std::make_unique<Client>(stoi(id),email,password,name));
            usersN++;
        }
        else if(role == "operator"){
            users.push_back(std::make_unique<Operator>(stoi(id),email,password,name));
            usersN++;
        }
        else{
            users.clear();
            throw ReadUsersException(static_cast<int>(usersN)+1);
        }
    }
}

void Manager::readMap(){

    mapFile.clear();
    mapFile.seekg(0,BEGIN);

    std::string line = "";

    getline(mapFile,line);

    while(getline(mapFile,line)){
        
        std::size_t tripId = stoi(readString(line));

        std::size_t clientId = stoi(readString(line));

        for(auto& trip: trips){
            if(trip->getId() == tripId){
                for(auto& user: users){
                    if(user->getId() == clientId){
                        Client *client = dynamic_cast<Client*>(user.get());
                        if(client){
                            client->getReservedTrips().push_back(trip);
                        }
                    }
                }
            }
        }
    }
    
}

void Manager::checkEmailFormat(const std::string& email){
    if(email.size() == 1)
        throw WrongEmailFormatException();

    if(email.find_first_of("@") == std::string::npos)
        throw WrongEmailFormatException();
    
    if(email.find_first_of("@") != email.find_last_of("@"))
        throw WrongEmailFormatException();

    std::size_t location = email.find("@");
    if(email.substr(0,location).size() == 0)
        throw WrongEmailFormatException();
    
    if(email.substr(location+1).size() == 0)
        throw WrongEmailFormatException();

    for(auto& x: users){
        if(x->getEmail() == email)
            throw EmailAlreadyExistsException();
    }
}

User* Manager::login(const std::string& email, const std::string& password){
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

std::size_t Manager::allocateId(std::vector<std::size_t>& idArray){
    std::sort(idArray.begin(),idArray.end());

    size_t validId = 1;

    for(std::size_t value: idArray){
        if(value == validId){
            validId++;
        }
        else if(value > validId){
            break;
        }
    }

    return validId;
}

void Manager::registerUser(const std::string& name,const std::string& email, const std::string& password){

    usersFile.clear();
    usersFile.seekp(0,END);

    std::streampos fileSize = usersFile.tellg();

    if(fileSize > 0){
       // check for last character in the file for proper writing
    usersFile.seekg(-1,END);
    char lastChar;
    usersFile.get(lastChar);
    if(lastChar !='\n')
        usersFile<< '\n'; 
    }
    
    usersFile.seekp(0,END);

    std::size_t allocatedId = allocateId(userIds); 
    // id, email, parola, role, name
    usersFile <<  allocatedId << "," << email << "," << password << ",client," << name << "\n";
    
    usersFile.flush(); // ensure data is written

    usersN++;
    
    userIds.push_back(allocatedId);
    users.push_back(std::make_unique<User>(allocatedId,email,password,"client",name));
}
std::string Manager::getOperatorName(std::size_t id){
    for(auto& user: users){
        if(user->getId() == id)
            {
                return user->getName();
            }
    }
    return "N/A";
}
void Manager::displayTrips(){
    std::cout<<"================\nHere are all the trips we have:\n";
    for(auto& trip: trips){
        trip->printInfo(*this);
    }
}

void Manager::displayReservedTrips(User& user){
    std::cout<<"================\nHere are all the trips we have for you:\n";
    for(auto& trip: (static_cast<Client&>(user)).getReservedTrips()){
        trip->printInfo(*this);
    }
}

void Manager::searchTrip(const std::string& keyword){
    std::cout<<"================\nHere are the trips matching your search:\n";
    for(auto& trip: trips){
        if(trip->getName().find(keyword) != std::string::npos ||
           trip->getCity().find(keyword) != std::string::npos ||
           trip->getDate().find(keyword) != std::string::npos){
                trip->printInfo(*this);
           }
    }
}

// id(_id), name(_name), city(_city), date(_date)
void Manager::registerTrip(Operator& operatorUser, const std::string& name, const std::string& city, const std::string& date){
    
    int dateValidation = isValidDate(date);
    if(dateValidation == 0)
        throw WrongDateFormatException();
    if(dateValidation == -1)
        throw PastDateException();

    tripsFile.clear();
    tripsFile.seekp(0,END);

    std::streampos fileSize = tripsFile.tellg();

    // check for last character in the file for proper writing
    if (fileSize> 0) {
    tripsFile.seekg(-1,END);
    char lastChar;
    tripsFile.get(lastChar);
    if(lastChar !='\n')
        tripsFile<< '\n';
    }

    tripsFile.seekp(0, END);

    size_t allocatedId = allocateId(tripIds);
    // id,operatorId,name,city,date
    tripsFile << allocatedId << "," << operatorUser.getId() << "," << name << "," << city << "," << date << "\n";
    
    tripsFile.flush(); // ensure data is written

    tripsN++;
    trips.push_back(std::make_shared<Trip>(allocatedId,operatorUser.getId(),name,city,date));
}

void Manager::reserveTrip(Client& client,std::size_t tripId){

    int tripExists = 0;
    int tripAlreadyReserved = 0;
    
    for(auto& trip: client.getReservedTrips()){
        if(trip->getId() == tripId){
            tripAlreadyReserved = 1;
            break;
        }
    }
    if(tripAlreadyReserved){
        throw AlreadyReservedException();
    }

    for(auto& trip: trips){
        if(trip->getId() == tripId){
            tripExists = 1;
            client.getReservedTrips().push_back(trip);
            break;
        }
    }

    if(!tripExists)
        throw InvalidTripIdException();

    mapFile.clear();
    mapFile.seekp(0,END);

    std::streampos fileSize = mapFile.tellg();

    if(fileSize > 0){
       // check for last character in the file for proper writing
    mapFile.seekg(-1,END);
    char lastChar;
    mapFile.get(lastChar);
    if(lastChar != '\n')
        mapFile<< '\n'; 
        
    }

    tripsFile.seekp(0,END);
    
    // tripId,clientID
    mapFile << tripId << "," << client.getId() << "";
    
    mapFile.flush(); // ensure data is written    
}

void Manager::unreserveTrip(Client& client, std::size_t tripId){
    auto& reserved = client.getReservedTrips();
    auto it = std::remove_if(reserved.begin(), reserved.end(),
                             [tripId](const std::shared_ptr<Trip>& t){ return t->getId() == tripId; });
    
    if(it == reserved.end()) {
        throw InvalidTripIdException();
    }

    
    reserved.erase(it, reserved.end());
    std::cout << "Trip unreserved from Client's memory.\n";

    // Delete the trip from the mapFile CSV (tripId,clientId)
    mapFile.clear();
    mapFile.seekg(0, BEGIN);
    std::string tempFileName = "temp.csv";
    std::ofstream tempFile(tempFileName);
    tempFile << "tripId,clientId\n"; // write header
    std::string line;
    std::getline(mapFile, line);
    while (std::getline(mapFile, line)) {
        std::size_t currentTripId = stoi(line.substr(0, line.find(',')));
        if (currentTripId != tripId) {
            tempFile << line << "\n";
        }
    }
    tempFile.close();
    mapFile.close();
    std::remove(mapFileName.c_str());
    std::rename(tempFileName.c_str(), mapFileName.c_str());

    mapFile.open(mapFileName, std::ios::in | std::ios::out);
}

// TODO : fix this
void Manager::deleteTrip(Operator& operatorUser, std::size_t tripId) {

    int tripExists = 0;
    for(auto& trip: trips){
        if(trip->getId() == tripId){   
            if(trip->getOperatorId() != operatorUser.getId())
                throw OperatorNotTripOwner();
            tripExists = 1;
            break;
        }
    }
    if(!tripExists)
        throw InvalidTripIdException();

    // Check if any client has reserved this trip
    for (auto& user : users) {
        if (user->getRole() == "client") {
            Client& client = dynamic_cast<Client&>(*user);
            for (auto& trip : client.getReservedTrips()) {
                if (trip->getId() == tripId) {
                    std::cout << "Cannot delete a trip that is reserved by users!\n";
                    return; // abort deletion
                }
            }
        }
    }

    // Delete the trip from Manager's trips vector
    auto it = std::remove_if(trips.begin(), trips.end(),
                             [tripId](const std::shared_ptr<Trip>& t){ return t->getId() == tripId; });
    if (it != trips.end()) {
        trips.erase(it, trips.end());
        std::cout << "Trip deleted from Manager's memory.\n";
    }

    // Remove the trip from all clients' reservedTrips (if needed)
    for (auto& user : users) {
        if (user->getRole() == "client") {
            Client& client = dynamic_cast<Client&>(*user);
            auto& reserved = client.getReservedTrips();
            reserved.erase(
                std::remove_if(reserved.begin(), reserved.end(),
                               [tripId](const std::shared_ptr<Trip>& t){ return t->getId() == tripId; }),
                reserved.end()
            );
        }
    }

    // Delete the trip from the mapFile CSV (tripId,clientId)
    tripsFile.clear();
    tripsFile.seekg(0, BEGIN);
    std::string tempFileName = "temp.csv";
    std::ofstream tempFile(tempFileName);
    tempFile << "id,operatorId,name,city,date\n"; // write header
    std::string line;
    std::getline(tripsFile, line);
    while (std::getline(tripsFile, line)) {
        std::size_t currentTripId = stoi(line.substr(0, line.find(',')));
        if (currentTripId != tripId) {
            tempFile << line << "\n";
        }
    }
    tempFile.close();
    tripsFile.close();
    std::remove(tripsFileName.c_str());
    std::rename(tempFileName.c_str(), tripsFileName.c_str());

    tripsFile.open(tripsFileName, std::ios::in | std::ios::out);

}
