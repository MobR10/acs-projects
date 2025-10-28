
/*
 Modelați din natură un exemplu de moștenire multiplă (multiple inheritance) care să conțină constructor default. 
*/

#include <iostream>
#include <string>
using namespace std;
 

class Cafea{
    private:
        int grame;
        double calorii;

    public:
        Cafea(): grame(0),calorii(0.0){
            cout<<"Constructor default cafea"<<endl;
        }
};

class Lapte{
    private:
        int gramaj;
        double calorii;
    public:
        Lapte(): gramaj(0.0),calorii(0.0){
            cout<<"Constructor default lapte"<<endl;
        }
};

class Cappucino: private Cafea, private Lapte{
    public:
        Cappucino(): Cafea{}, Lapte{} {
            cout<<"Constructor default cappucino"<<endl;
        }
};

int main(){
    Cappucino capp;
}   