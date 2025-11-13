#include <iostream>
#include <string>

using namespace std;

class ILogger{
    public:
    virtual void logMessage(string msg) = 0;

    virtual ~ILogger() = default;
};

class Dispozitiv{
    protected:
        string numeDispozitiv;
    
        virtual bool esteConectat() = 0;

    public:
        string getNume() const{
            return this->numeDispozitiv;
        }
};

class Imprimanta: public ILogger, public Dispozitiv{
    public:
        bool esteConectat() {
            return 1;
        }

        void logMessage(string msg){
            cout<<"Mesaj: "<<msg<<endl;
        }
};
int main(){
    Imprimanta imprimanta;

    imprimanta.logMessage("Salut");
    cout<<imprimanta.esteConectat();
}