// MY HEADERS
#include "../headers/Manager.h"
#include "../headers/Operator.h"

// C++
#include <iostream>
#include <string>

#include <limits>

using namespace std;

// macros
const string fisier = "users.csv";

#include "../headers/functions.h"

int main(){

    int userLogged = 0; 
    int run = 1;
    int once = 0;
    Manager manager(fisier);

    
    string email = "";
    do{
        if(!once){
        cout<<"Bine ai venit pe aplicatia BlaBlaCar de Vaslui!\n";
        once= 1;
        }   

        cout<<"\nTe rog sa selectezi una din operatiile de mai jos:"<<endl;

        switch(userLogged){
            case 0:
            cout<<
            "1. Register"<<endl<<
            "2. Login"<<endl<<
            "3. Vezi curse"<<endl<<
            "4. Exit"<<endl
            ;
            break;
            case 1:
            cout<<
            "1. Vezi curse"<<endl<<
            "2. Rezerva cursa"<<endl<<
            "3. Log out"<<endl<<
            "4. Exit"<<endl
            ;
            break;
        }

        cout<<"Waiting for input: ";
        string command = "";


        int ok = 1;
        do{
            ok = 1;
            getline(std::cin,command);
            std::cout<<endl<<"Input: "<<command<<endl;

            if(userLogged){
                if(!isValidInput(command,"1234")){
                    ok=0;
                }
                }
            else{
                if(!isValidInput(command,"1234")){
                    cout<<"aici";
                    ok=0;
                }
                
            }
            if(!ok) cout<<"Retry\n";
        }while(!ok);

        int option = stoi(command);
        cout<<option;


    }while(run);



    

    

}