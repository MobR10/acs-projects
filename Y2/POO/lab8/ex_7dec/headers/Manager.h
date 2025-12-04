#pragma once

#include "User.h"
#include "Client.h"
#include "Operator.h"

#include "exceptions/WeakPasswordException.h"
#include "exceptions/ShortPasswordException.h"
#include "exceptions/DifferentPasswordsException.h"

#include <fstream>
#include <string>
#include <vector>
#include <memory>

class Manager{
    std::string usersFileName;
    std::string tripsFileName;
    std::string mapFileName;
    std::fstream usersFile;
    std::fstream tripsFile;
    std::fstream mapFile;
    std::size_t usersN;
    std::size_t tripsN;
    std::vector<std::size_t> userIds;
    std::vector<std::size_t> tripIds;
    std::vector<std::unique_ptr<User>> users;
    std::vector<std::shared_ptr<Trip>> trips;
    
    void findTripsN();
    void readTrips();
    void readUsers();
    void findUsersN();

    void readMap();

    std::string readString(std::string& line);

    public:
        Manager(const std::string& usersFileName,const std::string& tripsFileName, const std::string& _mapFileName);

        ~Manager();

        std::size_t allocateId(std::vector<std::size_t>& idArray);

        template<typename T>
        std::string checkPassword(const T& password,const T& confirmPassword){
                    
            if(password != confirmPassword)
                throw DifferentPasswordsException();

            if(password.size() < 8)
                throw ShortPasswordException(8);
        
            std::string _password;

            if constexpr (std::is_same_v<T, std::string>)
                _password = password;   
            else
                _password = std::to_string(password); 

            int hasDigit = 0;
            int hasLetter = 0;
            int hasSymbol = 0;

            for (char c : _password) {
                if (std::isdigit(c)) hasDigit = 1;
                else if (std::isalpha(c)) hasLetter = 1;
                else hasSymbol = 1;
            }

            int factor = hasDigit + hasLetter + hasSymbol;
            // Evaluate strength
            if(factor == 3) return "good";
            if(factor == 2) return "ok";

            throw WeakPasswordException();
        }

        void checkEmailFormat(const std::string& email);

        void registerUser(const std::string& name,const std::string& email,const std::string& password);

        User* login(const std::string& email, const std::string& password);

        void logout(User*& user, int& userLoggedIn);

        // TRIPS

        std::string getOperatorName(std::size_t id);

        void reserveTrip(Client& client,std::size_t tripId);

        void unreserveTrip(Client& client, std::size_t tripId);

        void displayTrips();

        void searchTrip(const std::string& keyword);

        void displayReservedTrips(User& user);

        void deleteTrip(Operator& operatorUser, std::size_t tripId);

        void registerTrip(Operator& operatorUser,
        const std::string& _name,
        const std::string& _city,
        const std::string& _date);


};