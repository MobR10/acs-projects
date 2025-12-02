#pragma once
#include <vector>
#include <iostream>
#include "Item.h"
#include "MagicBook.h"

class Inventory {
private:
    std::vector<Item*> items; // We store pointers because Item is abstract-ish

public:
    Inventory() {
        std::cout << "Inventory created (Empty)\n";
    }

    // INTERN NOTE: I didn't write a Copy Constructor because C++
    // does it automatically, right? Less code = better!

    // Problem solver note: I made the copy constructor because C++
    // doesn't make it automatically!
    Inventory(const Inventory& obj) {
        items.reserve(obj.items.size());
        for (Item* p : obj.items) {
            items.push_back(p->clone());
            }
    }


    ~Inventory() {
        std::cout << "Inventory destructor: Cleaning up " << items.size() << " items...\n";
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i] != nullptr) {
                delete items[i]; // Delete the heap memory
            }
        }
        items.clear();
    }

    void addItem(Item* item) {
        items.push_back(item);
    }

    void listItems() const {
        std::cout << "\n--- Inventory Contents ---\n";
        for (const auto& item : items) {
            // Just printing the name for now
            std::cout << "- " << item->getName() << "\n";
        }
        std::cout << "--------------------------\n";
    }

    // Helper to access items for testing
    Item* getItem(int index) {
        if (index >= 0 && index < items.size()) {
            return items[index];
        }
        return nullptr;
    }
};
