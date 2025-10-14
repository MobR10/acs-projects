//  Creați o clasă Motor cu un constructor implicit care afișează "Motor pornit" și un destructor care afișează "Motor oprit".
//  Creați o clasă Mașină care are ca membru privat un obiect de tip Motor (de ex., Motor motor;).
//  Constructorul clasei Mașină va afișa "Mașină asamblată", iar destructorul va afișa "Mașină dezasamblată".
//  În main, creați o instanță a clasei Mașină, de exemplu: Mașină mașinaMea;.
//  Care este outputul exact al programului? De ce? 1P

#include <iostream>
using namespace std;

class Motor
{

public:
    Motor()
    {
        cout << "Motor pornit\n";
    }

    ~Motor()
    {
        cout << "Motor oprit\n";
    }
};

class Masina
{
    // Motor motor;

public:
    Masina()
    {
        cout << "Masina asamblata\n";
    }
    ~Masina()
    {
        cout << "Masina dezasamblata\n";
    }
    Motor motor;
};

int main()
{

    cout << "\nOrdinea in care sunt distruse elementele este pe baza de stiva, iar ordinea lor de construire este: mai intai \
sunt definite si construite datele membre din clasa, iar la final de tot sunt apelati constructorii.\n";
    Masina masinaSmechera;
}