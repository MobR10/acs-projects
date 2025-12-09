#include <iostream>
#include <string>

using namespace std;

class BoeingPlane{
    public:
    BoeingPlane(){
        cout<< "I am a boeing plane"<<endl;
    }

};

class FighterJetPlane{
    public:
    FighterJetPlane(){
        cout<< "I am a fighter jet plane"<<endl;
    }
};

class CargoPlane{
    public:
    CargoPlane(){
        cout<<"I am a cargo plane"<<endl;
    }
};

class PlaneFactory{
    public:
    virtual BoeingPlane* createBoeing() = 0;
    virtual FighterJetPlane* createFighterJet() = 0;
    virtual CargoPlane* createCargoPlane() = 0;
    virtual ~PlaneFactory() {};
};

class BoeingFactory: public PlaneFactory{
    public:
        BoeingPlane* createBoeing(){
            return new BoeingPlane();
        }

        FighterJetPlane* createFighterJet(){
            return nullptr;
        }

        CargoPlane* createCargoPlane(){
            return nullptr;
        }
};

class FighterJetFactory: public PlaneFactory{
    public:
        BoeingPlane* createBoeing(){
            return nullptr;
        }

        FighterJetPlane* createFighterJet(){
            return new FighterJetPlane();
        }

        CargoPlane* createCargoPlane(){
            return nullptr;
        }
};

class CargoPlaneFactory: public PlaneFactory{
    public:
        BoeingPlane* createBoeing(){
            return nullptr;
        }

        FighterJetPlane* createFighterJet(){
            return nullptr;
        }

        CargoPlane* createCargoPlane(){
            return new CargoPlane();
        }
};


int main(){
    string userInput = "";

    cout<<"Enter the type of plane you want (transport / fighter / cargo): ";
    do{
        getline(cin,userInput);
        if(userInput != "transport" && userInput != "fighter" && userInput != "cargo"){
            cout<<"Invalid input. Please enter again (transport / fighter / cargo): ";
        }

        if(userInput == "transport"){
                BoeingFactory* factory = new BoeingFactory();
                BoeingPlane* plane = factory->createBoeing();
                delete plane;
                delete factory;
                return 0;
            }
        else if (userInput == "fighter"){
                FighterJetFactory* factory = new FighterJetFactory();
                FighterJetPlane* plane = factory->createFighterJet();
                delete plane;
                delete factory;
                return 0;
            }
        else if (userInput == "cargo"){
                CargoPlaneFactory* factory = new CargoPlaneFactory();
                CargoPlane* plane = factory->createCargoPlane();
                delete plane;
                delete factory;
                return 0;
            }
    }while(true);


}