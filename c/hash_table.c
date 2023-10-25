#include <stdio.h>
#include <string.h>

unsigned int hash_division(unsigned int key, unsigned int table_size){
    return key % table_size; 
}

unsigned int multiplication_hash(unsigned int key, unsigned int table_size){
    float A = 0.618033; 
    float v = table_size * A;
    float  m = v - (unsigned int)(v);
    return table_size * m;
}

unsigned int string_to_key(const char *str, unsigned int table_size){
    unsigned int value = 7;
    for(int i = 0; i < strlen(str); i++){
        value = value * 31 + (unsigned int)(str[i]); 
    }
    return value;
}

typedef struct{
    unsigned int key;
    int is_ocupied;
    int value;
}OpenAddrSlot;

typedef struct ChainSlot{
    unsigned int key;
    int value;
    struct ChainSlot *next; 
}ChainSlot;


#define HASH_TABLE_CAPACITY 10

typedef struct
{
    int size;
    OpenAddrSlot data[HASH_TABLE_CAPACITY];
}HashTableOpenAddressing;

typedef struct
{
    int size;
    ChainSlot data[HASH_TABLE_CAPACITY];
}HashTableChaining;


void ht_open_addr_init(HashTableOpenAddressing *ht){
    *ht = (HashTableOpenAddressing){};
}

void ht_open_addr_display(HashTableOpenAddressing *ht){
    printf("[");
    for(int i = 0; i < HASH_TABLE_CAPACITY; i++){
        if(ht->data[i].is_ocupied)
            printf(" x ");
        else
            printf(" %00d ", ht->data[i].value); 

        if(i - 1 < HASH_TABLE_CAPACITY)
            printf("|");
    }
    printf("]\n");
}

