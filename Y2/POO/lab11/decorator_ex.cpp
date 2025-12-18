#include <iostream>
#include <string>
using namespace std;

class Shaorma {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
};

class EmptyShaorma : public Shaorma {
public:
    string getDescription() override {
        return "Empty Shaorma";
    }

    double getCost() override {
        return 0;
    }
};

class ShaormaDecorator : public Shaorma {
protected:
    Shaorma* decoratedShaorma;

public:
    ShaormaDecorator(Shaorma* decoratedShaorma) : decoratedShaorma(decoratedShaorma) {}

    string getDescription() override {
        return decoratedShaorma->getDescription();
    }

    double getCost() override {
        return decoratedShaorma->getCost();
    }
};

class PuiDecorator : public ShaormaDecorator {
public:
    PuiDecorator(Shaorma* decoratedShaorma) : ShaormaDecorator(decoratedShaorma) {}

    string getDescription() override {
        return decoratedShaorma->getDescription() + ", Pui";
    }

    double getCost() override {
        return decoratedShaorma->getCost() + 5;
    }
};

class VitaDecorator : public ShaormaDecorator {
public:
    VitaDecorator(Shaorma* decoratedShaorma) : ShaormaDecorator(decoratedShaorma) {}

    string getDescription() override {
        return decoratedShaorma->getDescription() + ", Vita";
    }

    double getCost() override {
        return decoratedShaorma->getCost() + 9;
    }
};

class VarzaDecorator : public ShaormaDecorator {
public:
    VarzaDecorator(Shaorma* decoratedShaorma) : ShaormaDecorator(decoratedShaorma) {}

    string getDescription() override {
        return decoratedShaorma->getDescription() + ", Varza";
    }

    double getCost() override {
        return decoratedShaorma->getCost() + 3;
    }
};

class KetchupDecorator : public ShaormaDecorator {
public:
    KetchupDecorator(Shaorma* decoratedShaorma) : ShaormaDecorator(decoratedShaorma) {}

    string getDescription() override {
        return decoratedShaorma->getDescription() + ", Ketchup";
    }

    double getCost() override {
        return decoratedShaorma->getCost() + 9;
    }
};

class CastravetiDecorator : public ShaormaDecorator {
public:
    CastravetiDecorator(Shaorma* decoratedShaorma) : ShaormaDecorator(decoratedShaorma) {}

    string getDescription() override {
        return decoratedShaorma->getDescription() + ", Castraveti";
    }

    double getCost() override {
        return decoratedShaorma->getCost() + 9;
    }
};
int main() {
    // Empty Shaorma
    Shaorma* empty = new EmptyShaorma();
    cout << "Description: " << empty->getDescription() << endl;
    cout << "Cost: $" << empty->getCost() << endl;

    // Shaorma with Milk
    Shaorma* shaormaCuVita = new VitaDecorator(new VarzaDecorator(new EmptyShaorma()));
    cout << "\nDescription: " << shaormaCuVita->getDescription() << endl;
    cout << "Cost: $" << shaormaCuVita->getCost() << endl;

    // Shaorma cu de toate
    Shaorma* shaormaCuDeToate = new VitaDecorator(new VarzaDecorator(new PuiDecorator(new CastravetiDecorator(new KetchupDecorator(new EmptyShaorma())))));
    cout << "\nDescription: " << shaormaCuDeToate->getDescription() << endl;
    cout << "Cost: $" << shaormaCuDeToate->getCost() << endl;

    delete empty;
    delete shaormaCuVita;
    delete shaormaCuDeToate;
    return 0;
}