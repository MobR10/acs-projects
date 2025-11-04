#include <iostream>
#include <string>

using namespace std;

class Persoana{
    private:
        string name;

    public:
        Persoana(string name): name(name){
        }

        void virtual printOccupation(){
            cout<<"Persoana: "<<"Sunt somer :("<<endl;
        }

        void virtual haiInOras(){
            cout<<"Persoana: "<<"Da, frate, dar tu platesti."<<endl;
        }
};

class Angajat: Persoana{
    private:
    string name;
    double salariu;

    public:
        Angajat(string name,double salariu): Persoana(name){
            this->salariu = salariu;
        }

        void printOccupation() override{
            cout<<"Angajat: "<<"Sunt un simplu angajat la o companie."<<endl;
        }

        void haiInOras() override{
            cout<<"Angajat: "<<"Sigur, dar stai sa vad daca am destui bani!"<<endl;
        }

        void printSalary(){
            cout<<"Angajat: "<<"salariu este "<<this->salariu;
        }
};

class Manager: Angajat{
    private:
    string name;
    double salariu;
    public:
        Manager(string name, double salarius): Angajat(name,salariu){
          this->salariu = salariu;  
        }

        void printOccupation() override{
            cout<<"Manager: "<<"Sunt Manager la o companie."<<endl;
        }

        void haiInOras() override{
            cout<<"Manager: "<<"Scuze, nu pot, lucrez si in weekend."<<endl;
        }
};

class Programator: Angajat{
    private:
    string name;
    double salariu;

    public:
        Programator(string name, double salariu): Angajat(name,salariu){
        }

        void printOccupation() override{
                cout<<"Programator: "<<"Sunt programator la o companie."<<endl;
            }

        void haiInOras() override{
            cout<<"Programator: "<<"Sigur, fac cinste!"<<endl;
        }

};

int main(){
    Persoana persoana("Bula");

    persoana.printOccupation();
    persoana.haiInOras();

    Angajat angajatSimplu("gigel",2000); 
    angajatSimplu.haiInOras();
    angajatSimplu.printOccupation();

    Manager manager("Chis",5000);
    manager.haiInOras();
    manager.printOccupation();

    Programator programator("Cosmin",3000);
    programator.haiInOras();
    programator.printOccupation();
}