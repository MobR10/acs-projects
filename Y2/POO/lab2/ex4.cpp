//  Acest exercițiu demonstrează principiul RAII (Resource Acquisition Is Initialization) folosind o resursă care nu este memoria.
//  Creați o clasă C++ numită ManagerFișier. Constructorul primește ca argument un const char* nume_fisier și deschide un fișier
//  pentru scriere folosind std::ofstream. La succes, va afișa mesajul "Fișier deschis."
//  O metodă void scrie(const std::string& mesaj) scrie o linie de text în fișier.
//  Destructorul trebuie să închidă fișierul și să afișeze mesajul "Fișier închis."
//  Funcția main: În main, creați o instanță a clasei ManagerFișier într-un bloc de cod ({ ... }). Apelați metoda scrie.
//  Observați cum fișierul este închis automat atunci când obiectul iese din scope.

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ManagerFisier{
    ofstream outputFile;

    public:
    ManagerFisier(const char* nume_fisier){
        outputFile.open(nume_fisier);

        if(outputFile.is_open())
            cout<<"Fisier deschis\n";
        else
            cout<<"Fisierul nu a putut fi deschis.\n";
    }

    ~ManagerFisier(){
        if(outputFile.is_open()){
            outputFile.close();
            cout<<"Fisierul a fost inchis.";
        }
    }

    void scrie(const string& mesaj){
        if(outputFile.is_open())
            outputFile<<mesaj;
    }
};

int main(){
    {
        ManagerFisier managerFisier("output.txt");
        managerFisier.scrie("pupici");
    }
}