// MY HEADERS
#include "../headers/Manager.h"
#include "../headers/Operator.h"
#include "../headers/User.h"

// C++
#include <iostream>
#include <string>

#include <limits>

using namespace std;

// macros
const string fisier = "users.csv";

#include "../headers/functions.h"

int main(){

    int userLoggedIn = 0; 
    int run = 1;
    int once = 0;

    User* user = NULL;

    Manager manager(fisier);

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
            cout<<
            "1. Vezi curse"<<endl<<
            "2. Rezerva cursa"<<endl<<
            "3. Log out"<<endl<<
            "0. Exit"<<endl
            ;
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
                if(!isValidInput(command,"0123")){
                    ok=0;
                }
                
            }
            if(!ok) cout<<"Invalid input. Retry: ";
        }while(!ok);

        int option = stoi(command);

        if(option == 0){
            cout<<"Terminating program...";
            exit(0);
        }
            
        if(!userLoggedIn)
            switch(option){
                // case 1: manager.register(); break;
                case 2: 
                string email = readValue("email");
                string password = readValue("password");
                user = manager.login(email,password); 
                if(!user)
                    cout<<"Wrong email or password. Try again"<<endl;
                else{
                    userLoggedIn = 1;
                    cout<<"Logged in succesfully!"<<endl<<"User: "<<user->getName()<<endl<<"Role: "<< user->getRole();
                }
                break;
                // case 3: manager.getTrips(); break;
            }
        else
            switch (option)
            {
            // case 1: manager.getTrips(); break;
            // case 2: manager.reserveTrip(); break;
            case 3: manager.logout(user,userLoggedIn); break;          
            }

    }while(run);



    

    

}