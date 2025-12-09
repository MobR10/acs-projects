#include <iostream>
#include <string>

using namespace std;

class Pizza{
    private:
    string dough,sauce;
    string toppings[4];
    int toppingCount = 0;

    public:
    void setDough(const string& _dough){
        this->dough = _dough;
    }

    void setSauce(const string& _sauce){
        this->sauce = _sauce;
    };

    void addTopping(const string& topping){
        if(toppingCount < 4){
            this->toppings[toppingCount++] = topping;
        }
        else{
            cout<<"Cannot add more toppings"<<endl;
        }
    }

    void display(){
        cout<<"Dough: "<<dough<<endl;
        cout<<"Sauce: "<<sauce<<endl;
        cout<<"Toppings: ";
        for(int i=0;i<toppingCount;i++){
            cout<<toppings[i]<<" ";
        }
        cout<<endl;
    }
};

class IPizzaBuilder{
    public:
    virtual IPizzaBuilder& reset() = 0;
    virtual IPizzaBuilder& buildDough(const string& dough) = 0;
    virtual IPizzaBuilder& buildSauce(const string& sauce) = 0;
    virtual IPizzaBuilder& addTopping(const string& topping) = 0;
    virtual Pizza getPizza() = 0;
    virtual ~IPizzaBuilder() {};
};

class PizzaBuilder: public IPizzaBuilder{
    private:
    Pizza pizza;

    public:
    IPizzaBuilder& reset() override{
        pizza = Pizza();
        return *this;
    }

    IPizzaBuilder& buildDough(const string& dough) override{
        pizza.setDough(dough);
        return *this;
    }

    IPizzaBuilder& buildSauce(const string& sauce) override{
        pizza.setSauce(sauce);
        return *this;
    }

    IPizzaBuilder& addTopping(const string& topping) override{
        pizza.addTopping(topping);
        return *this;
    }

    Pizza getPizza() override{
        return pizza;
    }
};

class Director{
    public:
        Pizza buildMargherita(PizzaBuilder& builder){
            builder.reset();
            builder.buildDough("Thin");
            builder.buildSauce("Tomato");
            builder.addTopping("Cheese");
            builder.addTopping("Basil");
            return builder.getPizza();
        }

        Pizza quatroStaggioni(PizzaBuilder& builder){
            builder.reset();
            builder.buildDough("Thick");
            builder.buildSauce("Tomato");
            builder.addTopping("Cheese");
            builder.addTopping("Ham");
            builder.addTopping("Mushrooms");
            builder.addTopping("Olives");
            return builder.getPizza();
        }
};

int main(){
    cout<<"Build your pizza!"<<endl<<endl;
    PizzaBuilder builder;
    Director director;
    cout<<"Margherita Pizza:"<<endl;
    Pizza pizza = director.buildMargherita(builder);
    pizza.display();

    cout<<"Quatro Staggioni Pizza:"<<endl;
    pizza = director.quatroStaggioni(builder);
    pizza.display();

    cout<<"Custom Pizza:"<<endl;
    pizza = builder.reset()
                    .buildDough("Stuffed")
                    .buildSauce("Pesto")
                    .addTopping("Cheese")
                    .addTopping("Tomatoes")
                    .addTopping("Chicken")
                    .addTopping("Spinach")
                    .getPizza();
    
    pizza.display();

    return 0;
}