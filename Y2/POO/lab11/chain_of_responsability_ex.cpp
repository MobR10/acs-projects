#include <iostream>
#include <string>

using namespace std;

class Handler;

class IHandler{
    public:
        virtual Handler* setNext(Handler* handler) { return nullptr;};
        virtual void handle(const string& request) = 0;
        ~IHandler(){}
};


class Handler: public IHandler{
    protected:
        Handler * next = nullptr;

    public:
        Handler* setNext(Handler* handler){
            this->next = handler;
            return handler;
        }

        virtual void handle(const string& request){
            if(next) next->handle(request);
        }
};

class CEO: public Handler{
    public:
    void handle(const string& request){
        if(request == "CEO")
            cout<<"CEO can solve this issue";
        else{
            Handler::handle(request);
        }
    }
};

class Manager: public Handler{
    public:
    void handle(const string& request){
        if(request == "manager")
            cout<<"Manager can solve this issue";
        else{
            Handler::handle(request);
        }
    }
};

class Programmer: public Handler{
    public:
    void handle(const string& request){
        if(request == "programmer")
            cout<<"Programmer can solve this issue";
        else{
            Handler::handle(request);
        }
    }
};



int main(){
    CEO *h1 = new CEO();
    Programmer *h3 = new Programmer();
    Manager *h2 = new Manager();

    h1->setNext(h2);
    h2->setNext(h3);

    h1->handle("programmer");
}