// MY HEADERS
#include "../headers/Manager.h"
#include "../headers/Operator.h"
#include "../headers/User.h"


#include "../headers/exceptions/DifferentPasswordsException.h"
#include "../headers/exceptions/WeakPasswordException.h"
#include "../headers/exceptions/ShortPasswordException.h"
#include "../headers/exceptions/WrongEmailFormatException.h"
#include "../headers/exceptions/EmailAlreadyExistsException.h"
#include "../headers/exceptions/InvalidTripIdException.h"
#include "../headers/exceptions/WrongDateFormatException.h"

// C++
#include <iostream>
#include <string>

#include <limits>

using namespace std;

// macros
const string users = "users.csv";
const string trips = "trips.csv";
const string map = "trips_clients_map.csv";

#include "../headers/functions.h"

int main(){

    int userLoggedIn = 0; 
    int run = 1;
    int once = 0;

    User* user = NULL;

    Manager manager(users,trips,map);

    do{
        if(!once){
        cout<<"Bine ai venit pe aplicatia BlaBlaCar de Vaslui!\n";
        once= 1;
        }   

        cout<<"\nTe rog sa selectezi una din operatiile de mai jos:"<<endl;

        if(!user){
            cout<<
            "1. Register"<<endl<<
            "2. Login"<<endl<<
            "3. Vezi curse"<<endl<<
            "0. Exit"<<endl
            ;
        } else{
            if(user->getRole() == "client"){
                cout<<
            "1. Vezi curse"<<endl<<
            "2. Rezerva cursa"<<endl<<
            "3. Vezi curse rezervate"<<endl<<
            "4. Log out"<<endl<<
            "0. Exit"<<endl
            ;
            }
            else{
               cout<<
            "1. Vezi curse"<<endl<<
            "2. Inregistreaza cursa"<<endl<<
            "3. Sterge cursa"<<endl<<
            "4. Log out"<<endl<<
            "0. Exit"<<endl
            ; 
            }
        }

        cout<<"Waiting for input: ";
        string command = "";


        int ok;
        do{
            ok = 1;
            getline(std::cin,command);
            std::cout<<endl<<"You entered: "<<command<<endl;

            if(!userLoggedIn){
                if(!isValidInput(command,"0123")){
                    ok=0;
                }
                }
            else{
                if(user->getRole() == "client"){
                    if(!isValidInput(command,"01234")){
                        ok=0;
                }
                }
                else{
                    if(!isValidInput(command,"01234")){
                        ok = 0;
                    }
                }
                
            }
            if(!ok) cout<<"Invalid input. Retry: ";
        }while(!ok);

        int option = stoi(command);

        if(option == 0){
            cout<<"Terminating program...";
            exit(0);
        }
        string name, email, password, confirmPassword,passwordStrength, city, date,id;
        if(!userLoggedIn)
            switch(option){
                case 1: // REGISTER
                name = readValue("name");

                emailInput:
                email = readValue("email");
                try{
                    manager.checkEmailFormat(email);
                }catch(const WrongEmailFormatException& e){
                    cout<<e.what();
                    goto emailInput;
                }catch(const EmailAlreadyExistsException& e){
                    cout<<e.what();
                    goto emailInput;
                }

                passwordsInput:
                password = readValue("password");
                confirmPassword = readValue("confirmPassword");
                try{
                    try{
                        passwordStrength= manager.checkPassword(password,confirmPassword);   
                    }catch(const WeakPasswordException& e){
                        cout<<e.what();
                        throw;
                    }catch(const ShortPasswordException& e){
                        cout<<e.what();
                        throw;
                    }catch(const DifferentPasswordsException& e){
                        cout<<e.what();
                        throw;
                    }
                }catch(...){
                    goto passwordsInput;
                }

                cout<<"Password strength: " + passwordStrength + "\n";
                manager.registerUser(name,email,password);
                break;
                case 2: // LOGIN
                email = readValue("email");
                password = readValue("password");
                user = manager.login(email,password); 
                if(!user)
                    cout<<"Wrong email or password. Try again"<<endl;
                else{
                    userLoggedIn = 1;
                    cout<<"Logged in succesfully!"<<endl<<"User: "<<user->getName()<<endl<<"Role: "<< user->getRole();
                }
                break;
                case 3: manager.displayTrips(); break;
            }
        else{
            if(user->getRole() == "client"){
                /*
                "1. Vezi curse"<<endl<<
            "2. Rezerva cursa"<<endl<<
            "3. Vezi curse rezervate"<<endl<<
            "4. Log out"<<endl<<
            "0. Exit"<<endl
                */
                switch (option){
                    case 1: manager.displayTrips(); break;
                    case 2: 
                    reserveID:
                    id = readValue("Trip Id");
                    try{
                        manager.reserveTrip(static_cast<Client&>(*user),stoi(id)); break;
                    }catch(const InvalidTripIdException& e){
                        cout<< e.what();
                        goto reserveID;
                    }
                    case 3:
                    manager.displayReservedTrips(*user);
                    break;
                    case 4: manager.logout(user,userLoggedIn); break;
                }
            }else{
                /*
                1. Vezi curse"<<endl<<
            "2. Inregistreaza cursa"<<endl<<
            "3. Sterge cursa"<<endl<<
            "4. Log out"<<endl<<
            "0. Exit"<<endl*/
                switch(option){
                    case 1: manager.displayTrips(); break;
                    case 2: 
                    name = readValue("name");
                    city = readValue("city");
                    dateInput:
                    date = readValue("date");
                    try{
                        manager.registerTrip(static_cast<Operator&>(*user),name,city,date); break;
                    }catch(const WrongDateFormatException& e){
                        cout<< e.what();
                        goto dateInput;
                    }
                    case 3: 
                    deleteId:
                    id = readValue("trip id");
                    try{
                        manager.deleteTrip(static_cast<Operator&>(*user),stoi(id));
                    }catch(const InvalidTripIdException& e){
                        cout<< e.what();
                        goto deleteId;
                    }
                    case 4:
                    manager.logout(user,userLoggedIn);
                }
            }
        }

    }while(run);



    

    

}