#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Component{
    public:
    virtual void execute() = 0;
    virtual void add(Component* c) {};
    ~Component(){}
};

class UI: public Component{
    vector<Component*> components;

    public:
    void add(Component* c){
        components.push_back(c);
    }

    void execute(){
        for(Component* c : components){
            c->execute();
        }
    }
};

class Button: public Component{
    public:
    void execute(){
        cout<<"Button pressed.\n";
    }
};

class Label: public Component{
    string text;
    public:
    Label(const string& _text): text(_text){}

    void execute(){
        cout<<"Label text is: " + text + "\n";
    }
};

class Window: public Component{
    vector<Component*> components;

    public:
    void add(Component* c){
        components.push_back(c);
    }

    void execute(){
        for(Component* c : components){
            c->execute();
        }
    }
};




int main(){
    UI *ui = new UI();

    Window *window = new Window();

    ui->add(window);
    
    window->add(new Button());
    window->add(new Label("Ce mai faci"));

    ui->execute();
}