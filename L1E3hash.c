#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 100

// comt: structure to represent an entry in the hash table
typedef struct HashEntry {
    char verb[50];
    int hash;
    struct HashEntry* next;
} HashEntry;

// initialize the hash table
HashEntry* hashTable[HASH_TABLE_SIZE];
int i;
// hash function for verbs
int hashFunction(const char* verb) {
    int hash = 0;
    for (i = 0; verb[i] != '\0'; i++) {
        hash += verb[i];
    }
    return hash % HASH_TABLE_SIZE;
}

// inserting verb into the hash table
void insert(const char* verb) {
    int hash = hashFunction(verb);

    // checking if the verb is already in the hash table
    HashEntry* current = hashTable[hash];
    while (current != NULL) {
        if (strcmp(current->verb, verb) == 0) {
            printf("Verb '%s' already exists in the hash table. Hash value: %d\n", verb, current->hash);
            return;
        }
        current = current->next;
    }

    // verb not found, insert it into the hash table
    HashEntry* newEntry = (HashEntry*)malloc(sizeof(HashEntry));
    strcpy(newEntry->verb, verb);
    newEntry->hash = hash;
    newEntry->next = hashTable[hash];
    hashTable[hash] = newEntry;
    printf("Verb '%s' inserted into the hash table. Hash value: %d\n", verb, hash);
}

// searching for a verb in the hash table
int search(const char* verb) {
    int hash = hashFunction(verb);

    // look for the verb in the hash table
    HashEntry* current = hashTable[hash];
    while (current != NULL) {
        if (strcmp(current->verb, verb) == 0) {
            return current->hash;
        }
        current = current->next;
    }

    //verb not found
    return -1;
}

int main() {
    char inputVerb[50];
    char option;

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    while (1) {
        printf("Enter an option (I for insert, S for search, Q to quit): ");
        scanf(" %c", &option);

        if (option == 'Q' || option == 'q') {
            break;
        }

        printf("Enter a verb: ");
        scanf("%s", inputVerb);

        switch (option) {
            case 'I':
            case 'i':
                insert(inputVerb);
                break;

            case 'S':
            case 's':
                {
                    int result = search(inputVerb);
                    if (result != -1) {
                        printf("Verb '%s' found in the hash table. Hash value: %d\n", inputVerb, result);
                    } else {
                        printf("Verb '%s' not found in the hash table.\n", inputVerb);
                    }
                }
                break;

            default:
                printf("Invalid option. Please enter I, S, or Q.\n");
                break;
        }
    }

    return 0;
} 
