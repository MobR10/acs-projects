/*  
    Se va  crea o clasă ContBancar care modelează un scenariu real.
    Construiti o clasă robustă care gestionează conturi bancare, separând datele specifice fiecărui
    cont de cele comune tuturor conturilor. 
    Cerințe:
    -> Clasa ContBancar: Va avea datele membre private: string titularCont & double sold
    -> Constructorul: Va primi titularul și soldul inițial pentru a crea un nou cont.
    -> Metode de Acces (Getters): getTitular(): Returnează numele titularului & getSold(): Returnează soldul curent. 
    Important: Ambele metode trebuie marcate ca const. De ce? Pentru că ele doar "citesc" starea contului, nu o modifică.
    Este o promisiune de siguranță.
    -> Metode pentru Tranzacții: depune(double suma): Adaugă suma specificată la sold & 
    retrage(double suma): Scade suma din sold, dar doar dacă există fonduri suficiente.
    Dacă nu, afișează un mesaj de eroare și soldul rămâne neschimbat.
    -> Date Partajate (Membru static): Toate conturile dintr-o bancă au aceeași dobândă. 
    Vom modela acest lucru cu un membru private static double rataDobanda.
    -> Acțiuni la Nivel de Clasă (Metode static): Adaugă o metodă public static void seteazaRataDobanda(double rataNoua).
    Această metodă va fi folosită de "bancă" pentru a schimba dobânda pentru toate conturile existente și viitoare.
    Se va apela direct pe clasă: ContBancar::seteazaRataDobanda(...). Adaugă o metodă non-statică numită aplicaDobanda().
    Aceasta calculează dobânda pentru contul curent (sold * rataDobanda) și o adaugă la sold.
*/

#include <iostream>
#include <string>

using namespace std;

class ContBancar{

    string titularCont;
    double sold;
    static double rataDobanda;

    public:
    ContBancar(string titularCont, double sold){
        this->titularCont = titularCont;
        this->sold = sold;
    }

    string getTitular() const{
        return this->titularCont;
    }

    double getSold() const{
        return this->sold;
    }

    void depune(double suma){
        (this->sold) += suma;
        cout<<"Succes depunere suma de "<<suma<<" in contul lui "<<this->titularCont<<endl;
    }

    void retrage(double suma){
        if(this->sold >= suma)
        {
            (this->sold) -= suma;
            cout<<"Succes retragere suma de "<<suma<<" din contul lui "<<this->titularCont<<endl;
        }
        else cout<<"Eroare retragere suma de "<< suma <<" din contul lui "<< this->titularCont<<". Sold < suma de retras"<<endl;
    }

    static void seteazaRataDobanda(double rataNoua){
        ContBancar::rataDobanda = rataNoua;
        cout<<"Rata Dobanda actualizata la "<<ContBancar::rataDobanda<<endl;
    }

    void aplicaDobanda(){
        (this->sold) += this->sold * ContBancar::rataDobanda;
        cout<<"S-a aplicat rata dobanda la soldul contului de titular"<<this->titularCont<<endl;
    }
};

double ContBancar::rataDobanda = 0.02;

int main(){
    ContBancar cont1("Stefan Tipatescu",21.4), cont2("Zoe Trahanache",68.99);

    cout<<"Cont1:"<<endl<<"Titular cont: "<<cont1.getTitular()<<endl<<"Sold initial: "<<cont1.getSold()<<endl;
    cout<<"Cont2:"<<endl<<"Titular cont: "<<cont2.getTitular()<<endl<<"Sold initial: "<<cont2.getSold()<<endl;

    cout<<endl;

    cont1.depune(20);
    cout<<"Cont1 sold: "<<cont1.getSold()<<endl;

    cont1.retrage(50.23);

    cont2.retrage(30.89);
    cout<<"Cont2 sold: "<<cont2.getSold()<<endl;

    cout<<endl;

    ContBancar::seteazaRataDobanda(0.07);

        cont1.aplicaDobanda();
    cont2.aplicaDobanda();

    cout<<"Cont1 sold: "<<cont1.getSold()<<endl;
    cout<<"Cont2 sold: "<<cont2.getSold()<<endl;
}
