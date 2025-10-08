#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Node for the linked list (chaining)
typedef struct HashNode {
    char* key;
    int value;
    struct HashNode* next;
} HashNode;

// Hash table structure
typedef struct {
    HashNode** buckets;
} HashTable;

// Simple hash function (djb2)
unsigned int hash(const char* str) {
    unsigned int sum = 0;
    while (*str) {
        sum += (unsigned int)(*str); // add ASCII value of each character
        str++;
    }
    return sum % TABLE_SIZE;
}

// Create a new hash node
HashNode* createNode(const char* key, int value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strdup(key); // duplicate key string
    node->value = value;
    node->next = NULL;
    return node;
}

// Create hash table
HashTable* createTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (HashNode**)calloc(TABLE_SIZE, sizeof(HashNode*));
    return table;
}

// Insert key-value
void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key);
    HashNode* node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value; // update
            return;
        }
        node = node->next;
    }

    // not found, insert new at beginning
    HashNode* newNode = createNode(key, value);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// Search key
int* search(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    HashNode* node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0)
            return &node->value;
        node = node->next;
    }
    return NULL;
}

int* delete(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    HashNode* node = table->buckets[index];
    HashNode* prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            int* value = (int*)malloc(sizeof(int));
            *value = node->value;

            if (prev == NULL) {
                // Deleting the first node in the list
                table->buckets[index] = node->next;
            } else {
                // Bypass the node
                prev->next = node->next;
            }

            free(node->key);  // free the duplicated key string
            free(node);
            return value;
        }

        prev = node;
        node = node->next;
    }

    printf("Can't delete the element with key '%s'. It doesn't exist.\n", key);
    return NULL;
}


// Free hash table
void freeTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// Example usage
int main() {
    HashTable* table = createTable();

    insert(table, "bicicleta", 5);
    insert(table, "mercedes", 3);
    insert(table, "bmw", 7);

    int* value= search(table, "mercedes");
    if (value)
    {
        value=delete(table,"mercedes");
        if(value)
            printf("Valoarea din mercedes a fost stearsa cu succes. Numarul eliminat este: %d\n",*value);
    }    
    else
        printf("Mercedes nu exista in dictionar\n");

    value = search(table, "bicicleta");
    if (value)
        printf("bicicleta => %d\n", *value);
    else
        printf("bicicleta nu exista\n");

    free(value);
    freeTable(table);
    return 0;
}
