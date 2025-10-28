/*
    Realizați o clasă Beer, care să conțină atributele type și origin (ambele string și să fie protected).
Clasa trebuie să aibă:
- Un constructor default
- Un constructor care va inițializa toți parametrii
- Metode de get pentru cei doi parametrii
    Din clasa Beer derivați alte 3 clase printr-o moștenire private. Fiecare va avea un tip diferit de etichetă pe sticlă
Tipul A: etichetă pătrată (private length)
Tipul B: etichetă rotundă și transparentă (private radius)
Tipul C: în formă de triunghi dreptunghic (private base și height)
Fiecare clasă va avea constructori default și constructori cu parametrii care să seteze fiecare atribut.
Fiecare clasă trebuie să aibă o metodă de a întoarce aria etichetei, a tipului și a originii.
*/

#include <iostream>
#include <string>

using namespace std;

class Beer{
    protected:
        string type , origin;

    public:
        Beer(){
            this->type = "Default";
            this->origin = "Default";
        }

        Beer(string val1, string val2){
            this->type = val1;
            this->origin = val2;
        }

        string getType() const{
            return this->type;
        }

        string getOrigin() const{
            return this->origin;
        }

         void displayAttributes() const{
            cout<<"Type: "<<this->type<<endl<<"Origin: "<<this->origin<<endl;
        }
};

class TypeA: private Beer{
    private: 
        double length;

    public:
        TypeA(){
            this->length = 0.0;
        }

        TypeA(string type, string origin, double length): Beer{type,origin}{
            this->length = length;
        }

        using Beer::getType;
        using Beer::getOrigin;

        double getArea() const{
            return this->length*this->length;
        }

        void displayAttributes() const {
            Beer::displayAttributes();
            cout<<"Length: "<< this->length<<endl;
        }
};

class TypeB: private Beer{
    private:
        double radius;
    public:

        TypeB(): radius(0.0) {

        }

        TypeB(string type, string origin,double radius): Beer{type,origin}, radius(radius){
            // this->radius = radius;
        }

        using Beer::getType;
        using Beer::getOrigin;

        double getArea() const{
            return this->radius*this->radius*3.14;
        }

         void displayAttributes() const {
            Beer::displayAttributes();
            cout<<"Radius: "<< this->radius<<endl;
        }
};

class TypeC: private Beer{
    private:
        double base, height;
    
    public:

        TypeC(){
            this->base = 0.0;
            this->height = 0.0;
        }

        TypeC(string type, string origin,double base, double height): Beer{type,origin}{
            this->base = base;
            this->height = height;
        }
        
        using Beer::getType;
        using Beer::getOrigin;

        double getArea() const{
            return this->base * this->height / 2;
        }

         void displayAttributes() const {
            Beer::displayAttributes();
            cout<<"Base: "<< this->base<<endl<<"Height: "<< this->height<<endl;
        }
};
int main()
{
    Beer beer("Sal","sal2");
    TypeA bereA("Mahmureala","Atlantis",12.);
    TypeB bereB("Rodie","Caras-Severin",4.32);
    TypeC bereC("Nu stiu","Cluj",2,5);


    beer.displayAttributes(); cout<<endl;
    bereA.displayAttributes(); cout<<endl;
    bereB.displayAttributes(); cout<<endl;
    bereC.displayAttributes(); cout<<endl;


}