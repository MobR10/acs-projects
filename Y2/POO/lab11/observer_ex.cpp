#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ISubscriber{
    public:
    virtual void update(const string& masa) = 0;
    ~ISubscriber(){}
};

class IRaphahell{
    vector<ISubscriber*> abonatii;
    public:
    void subscribe(ISubscriber *s){
        abonatii.push_back(s);
    }
    void notifica(const string& mesaj){
        for(auto s: abonatii){
            s->update(mesaj);
        }
    }

    void postezVideo(const string& titlu){
        cout<<"Iraphahell: " + titlu <<endl;
        notifica("A POSTAT IRAPHAHELL " + titlu + "\n");
    }

    void postezShort(const string& titlu){
        cout<<"Iraphahell: "+ titlu <<endl;
        notifica("A POSTAT IRAPHAHELL!!!");
    }

    void postezPostare(const string& titlu){
        cout<<"Iraphahell: " + titlu<<endl;
        notifica("Postare de la Iraphahell");
    }
};

class AppALert: public ISubscriber{
    public:
    void update(const string& msg){
        cout<<"Notificare app: "<< msg <<endl;
    }
};

int main(){

    IRaphahell *canal = new IRaphahell();

    canal->subscribe(new AppALert());

    canal->postezVideo("WEEKEND-UL HORROR EP20");
    canal->postezShort("Fiti atenti la faza asta");
    canal->postezPostare("M-am tuns");
}