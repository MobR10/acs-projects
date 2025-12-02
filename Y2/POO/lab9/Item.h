#pragma once
#include <iostream>
#include <string>

// INTERN NOTE: Base class for all things in the game
class Item {
protected:
    std::string name;

public:
    Item(const std::string& n) : name(n) {
        std::cout << "Item constructor: " << name << "\n";
    }

    // TODO: Boss said something about virtual here?
    // But it works fine without it on my machine.
    virtual ~Item() {
        std::cout << "Item destructor: " << name << "\n";
    }

    std::string getName() const { return name; }

    // This should be overridden, right?
    virtual void use() {
        std::cout << "Using a generic item: " << name << "\n";
    }

    virtual Item* clone() const = 0;
};

class Sword : public Item {
private:
    int damage;

public:
    Sword(const std::string& n, int dmg) : Item(n), damage(dmg) {
        std::cout << "Sword constructor\n";
    }

    ~Sword() {
        std::cout << "Sword destructor (Cleaning up blade oil...)\n";
    }

    void use() override {
        std::cout << "Swinging sword " << name << " for " << damage << " damage!\n";
    }

    Item* clone() const {
        return new Sword(*this);
    }

    int getMultiplier(int numerator, int denumerator){
        if(denumerator == 0)
            return 0;
        return numerator/denumerator;
    }

    void crit(int numerator, int denumerator){
        std::cout<<"Dealing crit dmg with sword: "<<damage + damage * getMultiplier(numerator,denumerator)<<std::endl;
    }
};

class Potion : public Item {
private:
    std::string type; // e.g., "Health", "Mana"

public:
    Potion(const std::string& n, const std::string& t) : Item(n), type(t) {
        std::cout << "Potion constructor\n";
    }

    ~Potion() {
        std::cout << "Potion destructor (Glass shattered)\n";
    }

    void use() override {
        std::cout << "Drinking " << type << " potion: " << name << "\n";
    }

    Item* clone() const{
        return new Potion(*this);
    }
};
