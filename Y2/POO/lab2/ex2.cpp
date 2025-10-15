// Să se implementeze o clasă Motorbike. Această clasă trebuie să aibă constructori multiplii (minim 4).
// Constructorii trebuie să fie definiți în afara clasei.
// Clasa Motorbike trebuie să aibă minim 4 atribute și un constructor să fie de tipul default.
// Creați un obiect pentru fiecare constructor.

#include <iostream>
#include <string>
using namespace std;

class Motorbike
{
public:
    string producer, model, engine;
    int year;
    float price;

    Motorbike();
    Motorbike(string producer, string model, string engine);
    Motorbike(string producer, string model, string engine, int year);
    Motorbike(string producer, string model, string engine, int year, float price);

    ~Motorbike() {}

    void displayMotorbike()
    {
        cout << "Producer: " << producer << endl;
        cout << "Model: " << model << endl;
        cout << "Engine: " << engine << endl;
        cout << "Year: " << year << endl;
        cout << "Price: " << price << endl;
    }
};

Motorbike::Motorbike()
{
    this->producer = "N/A";
    this->model = "N/A";
    this->engine = "N/A";
    this->year = -1;
    this->price = -1.;
}

Motorbike::Motorbike(string producer, string model, string engine)
{
    this->producer = producer;
    this->model = model;
    this->engine = engine;
    this->year = -1;
    this->price = -1.;
}

Motorbike::Motorbike(string producer, string model, string engine, int year)
{
    this->producer = producer;
    this->model = model;
    this->engine = engine;
    this->year = year;
    this->price = -1.;
}

Motorbike::Motorbike(string producer, string model, string engine, int year, float price)
{
    this->producer = producer;
    this->model = model;
    this->engine = engine;
    this->year = year;
    this->price = price;
}

int main()
{
    Motorbike motor1;
    Motorbike motor2("Honda", "CB500F", "471 cc, parallel-twin, liquid-cooled, 47 hp");
    Motorbike motor3("BMW Motorrad", "R 1250 GS", "1,254 cc, flat-twin (boxer), liquid/air-cooled, 136 hp", 2023);
    Motorbike motor4("Yamaha", "YZF-R1", "998 cc, inline 4-cylinder, liquid-cooled, 200 hp", 2023, 1203.99f);

    cout << "Motorbike1:\n";
    motor1.displayMotorbike();
    cout << "Motorbike2:\n";
    motor2.displayMotorbike();
    cout << "Motorbike3:\n";
    motor3.displayMotorbike();
    cout << "Motorbike4:\n";
    motor4.displayMotorbike();
}