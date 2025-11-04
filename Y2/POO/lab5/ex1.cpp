#include <iostream>

using namespace std;

#define PI 3.14

// consideram o piramida patrulatera regulata
class Volume{

    public:
    Volume() = default;

    void calculateVolume(int length){
        cout<<"Volumul cubului e: "<<length*length*length<<endl;
    }

    void calculateVolume(float radius){
        cout<<"Volumul sferei este: "<< 4 * PI * radius * radius * radius / 3<<endl;
    }

    void calculateVolume(double baseLength, double pyramidHeight){
        cout<<"Volumul piramidei este: "<< baseLength * baseLength * pyramidHeight / 2<<endl;
    }

    void calculateVolume(){
        cout<<"Introdu macar un parametru"<<endl;
    }
};


int main(){

    Volume calculator;

    calculator.calculateVolume();
    calculator.calculateVolume(3);
    calculator.calculateVolume(5.2f);
    calculator.calculateVolume(5.2,2.4);


}

