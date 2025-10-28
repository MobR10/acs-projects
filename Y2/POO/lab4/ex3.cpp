/*
==================================================================================================
    Clasa Baza:
- Creează o clasă Baza cu 3 metode simple. Fiecare metodă afișează doar numele ei (de ex. "Apel Baza::metodaPublica").
- public void metodaPublica()
- protected void metodaProtected()
- private void metodaPrivata()
    Clasa DerivataProtected:
- Moștenește protected din Baza (class DerivataProtected : protected Baza).
- În interiorul clasei (în secțiunea public), scrie o metodă void testAccesInterior() care încearcă să apeleze
toate cele 3 metode din Baza: metodaPublica(), metodaProtected(), metodaPrivata().
    Clasa DerivataPrivata:
- Moștenește private din Baza (class DerivataPrivata : private Baza).
- Similar, scrie o metodă public void testAccesInterior() care încearcă să apeleze toate cele 3 metode din Baza.

    Testul în main:
- Creează un obiect DerivataProtected objProt;.
- Încearcă să apelezi objProt.metodaPublica(). Compilează?
- Apelează objProt.testAccesInterior().
- Creează un obiect DerivataPrivata objPriv;.
- Încearcă să apelezi objPriv.metodaPublica(). Compilează?
- Apelează objPriv.testAccesInterior().
    Intrebari
- În testAccesInterior din ambele clase derivate, care dintre cele 3 apeluri nu a compilat și de ce?
- În main, de ce apelul objProt.metodaPublica() nu a compilat, deși era public în Baza?
- De ce objPriv.metodaPublica() nu a compilat? 
==================================================================================================
*/

#include <iostream>
#include <string>

using namespace std;

class Baza{
    public:
    void metodaPublica(){
        cout<<"Apel Baza::metodaPublica()"<<endl;
    }

    protected:
        void metodaProtected(){
            cout<<"Apel Baza::metodaProtected()"<<endl;
        }

    private:
        void metodaPrivata(){
        cout<<"Apel Baza::metodaPrivata()"<<endl;
        }
};

class DerivataProtected: protected Baza{
    public:
        void testAccesInterior(){
            metodaPublica();
            metodaProtected();
            // this->metodaPrivata();
        }
};

class DerivataPrivata: private Baza{
    public:
        void testAccesInterior(){
            metodaPublica();
            metodaProtected();
            // this->metodaPrivata();
        }
};

int main(){
    DerivataProtected objProt;
    // nu poate fi apelata, pentru ca metodaPublica este protected si inaccesibila din afara clasei objProt
    // objProt.metodaPublica(); 
    cout<<"objProt.metodaPublica() nu compileaza, pentru ca metodaPublica este protected si inaccesibila din afara clasei DerivataProtected"<<endl;
    objProt.testAccesInterior();

    DerivataPrivata objPriv;
    // nu compileaza pentru ca acum metodaPublica este private si inaccesibila din afara clasei objPriv
    // objPriv.metodaPublica();
    cout<<"objPriv.metodaPublica() nu compileaza pentru ca  metodaPublica e privata si inaccesibila din afara clasei DerivataPrivata"<<endl;
    objPriv.testAccesInterior();

    cout<<"Raspunsuri la intrebari:\n1. "<< "Doar al 3 lea apel nu a compilat, pentru ca in clasa baza metoda este in campul privat "
    "ceea ce o face inaccesibila si subclaselor sale\n";
    cout<<"2. Apelul objProt.metodaPublica() nu a compilat, pentru ca clasa DerivataProtected mosteneste Baza in mod protected "
    ", ceea ce transforma implicit toate metodele si atributele din Baza in protected pentru clasa copil, adica private fata de exteriorul "
    "clasei.\n";
    cout<<"3. Apelul objPriv.metodaPublica() nu a compilat, pentru ca mosteneste Baza in regim privat, deci toate atributele si metodele "
    "mostenite devin implicit de tip private, deci Baza::metodaPublica() e inaccesibila din afara";


}