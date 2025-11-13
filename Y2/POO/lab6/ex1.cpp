#include <iostream>
#include <string>

using namespace std;


class City{
    protected:
        string name;
        int countyCode;

        City(string name, int countyCode): name(name), countyCode(countyCode){}
        virtual string getName() = 0;
        virtual int getCountyCode() = 0;
        virtual string getType() = 0;
        
        virtual ~City(){cout<<"DESTRUCTOR BAZA\n";};
};

class Rural: public City{

    public:
    Rural(string name = "N/A", int countyCode = 0): City(name,countyCode){}
    string getName(){
        return this->name;
    }

    int getCountyCode(){
        return this->countyCode;
    }

    string getType(){
        cout<<"Im a rural city\n";
        return "rural";
    }
    
};

class Industrial: public City{
public:
    Industrial(string name = "N/A", int countyCode = 0): City(name,countyCode){}
    string getName(){
        return this->name;
    }

    int getCountyCode(){
        return this->countyCode;
    }

    string getType(){
        cout<<"Im an industrial city\n";
        return "industrial";
    }

};

class Port: public City{
public:
    Port(string name = "N/A", int countyCode = 0): City(name,countyCode){}
    string getName(){
        return this->name;
    }

    int getCountyCode(){
        return this->countyCode;
    }

    string getType(){
        cout<<"Im a port city\n";
        return "port";
    }
};

int main(){

    Rural orasRural("Las Fierbinti",50);
    cout<<orasRural.getName()<<endl;
    cout<<orasRural.getCountyCode()<<endl;
    orasRural.getType();

    Industrial orasIndustrial("Londra",12);
    cout<<orasIndustrial.getName()<<endl;
    cout<<orasIndustrial.getCountyCode()<<endl;
    orasIndustrial.getType();

    Port orasPort("Mangalia",67);
    cout<<orasPort.getName()<<endl;
    cout<<orasPort.getCountyCode()<<endl;
    orasPort.getType();

}