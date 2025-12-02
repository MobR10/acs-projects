#pragma once

#include <iostream>
#include <string>

#include "Item.h"

class MagicBook: public Item {
    std::string* spells;
    size_t count;          

public:
    // Constructor: takes external array of strings
    MagicBook(std::string name,const std::string* _spells, size_t _count)
        : Item(name),spells(nullptr), count(_count)
    {
        std::cout << "Constructor MagicBook\n";

        spells = new std::string[count];
        for (size_t i = 0; i < count; i++) {
            spells[i] = _spells[i];   // deep copy each string
        }
    }

    // Copy constructor (deep copy)
    MagicBook(const MagicBook& other)
        : Item(other.name), spells(nullptr), count(other.count)
    {
        spells = new std::string[count];
        for (size_t i = 0; i < count; i++) {
            spells[i] = other.spells[i];
        }
    }

    // Copy assignment
    MagicBook& operator=(const MagicBook& other) {
        if (this == &other)
            return *this;

        delete[] spells;

        name = other.name;
        count = other.count;
        spells = new std::string[count];
        for (size_t i = 0; i < count; i++) {
            spells[i] = other.spells[i];
        }

        return *this;
    }

    // Destructor
    ~MagicBook() {
        std::cout << "Destructor MagicBook\n";
        delete[] spells;
    }

    Item* clone() const {
        return new MagicBook(*this);
    }

    void use(){
        std::cout<<"Using MagicBook "<< name<<std::endl;
    }
    

};
