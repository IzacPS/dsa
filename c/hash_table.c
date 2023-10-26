#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USE_DIVISION_HASH
//#define USE_MULTIPLICATION_HASH
//#define USE_UNIVERSAL_HASH

#define USE_LINEAR_PROBE
//#define USE_QUADRATIC_PROBE
//#define USE_DOUBLE_HASH

unsigned int hash_division(unsigned int key, unsigned int table_size){
    return key % table_size; 
}

unsigned int hash_multiplication(unsigned int key, unsigned int table_size){
    float A = 0.618033; 
    float v = key * A;
    float  m = v - (unsigned int)(v);
    return table_size * m;
}

unsigned int string_to_key(const char *str){
    unsigned int value = 7;
    for(int i = 0; i < strlen(str); i++){
        value = value * 31 + (unsigned int)(str[i]); 
    }
    return value;
}

unsigned int hash_universal(unsigned int key, unsigned int table_size){
    unsigned int p = 122827;
    unsigned int a = 1 + rand() % p;
    unsigned int b = rand() % p;
    return ((a * key + b) % p) % table_size;
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


#define HASH_TABLE_CAPACITY 13

typedef struct
{
    int size;
    OpenAddrSlot data[HASH_TABLE_CAPACITY];
}HashTableOpenAddressing;

typedef struct
{
    int size;
    ChainSlot *data[HASH_TABLE_CAPACITY];
}HashTableChaining;


void ht_open_addr_init(HashTableOpenAddressing *ht){
    srand(time(NULL));
    memset(ht, 0,sizeof(*ht));
}

void ht_open_addr_display(HashTableOpenAddressing *ht){
    printf("[");
    for(int i = 0; i < HASH_TABLE_CAPACITY; i++){
        if(ht->data[i].is_ocupied)
            printf(" %03d ", ht->data[i].value); 
        else
            printf(" x ");

        if(i + 1 < HASH_TABLE_CAPACITY)
            printf("|");
    }
    printf("]\n");
}

void ht_open_addr_insert(HashTableOpenAddressing *ht, unsigned int key, int value){
    if(ht->size == HASH_TABLE_CAPACITY)
        return;
#if defined(USE_DIVISION_HASH)
    unsigned int index = hash_division(key, HASH_TABLE_CAPACITY); 
#elif defined(USE_MULTIPLICATION_HASH)
    unsigned int index = hash_multiplication(key, HASH_TABLE_CAPACITY);
#else
    unsigned int index = hash_universal(index, HASH_TABLE_CAPACITY);
#endif

    printf("index before: %d, ", index);
#if defined(USE_LINEAR_PROBE)
    int i = 0;
    for(; ht->data[index].is_ocupied && i < HASH_TABLE_CAPACITY; i++){
        index = (index + i) % HASH_TABLE_CAPACITY;
    }
    if(i < HASH_TABLE_CAPACITY){
        ht->data[index].key = key;
        ht->data[index].value = value;
        ht->data[index].is_ocupied = 1;
        ht->size++;
    }
#elif defined(USE_QUADRATIC_PROBE)
    unsigned int c1 = 3;
    unsigned int c2 = 5;
    int i = 0;
    for(; ht->data[index].is_ocupied && i < HASH_TABLE_CAPACITY; i++){
        index = (index + (c1 * i) + (c2 * i * i)) % HASH_TABLE_CAPACITY;
    }
    if(i < HASH_TABLE_CAPACITY){
        ht->data[index].key = key;
        ht->data[index].value = value;
        ht->data[index].is_ocupied = 1;
    }
#endif
    printf("index after: %d\n", index);
}

void ht_open_addr_delete(HashTableOpenAddressing *ht, unsigned int key){
#if defined(USE_DIVISION_HASH)
    unsigned int index = hash_division(key, HASH_TABLE_CAPACITY); 
#elif defined(USE_MULTIPLICATION_HASH)
    unsigned int index = hash_multiplication(key, HASH_TABLE_CAPACITY);
#else
    unsigned int index = hash_universal(index, HASH_TABLE_CAPACITY);
#endif

#if defined(USE_LINEAR_PROBE)
    int i = 0;
    for(; ht->data[index].key != key && i < HASH_TABLE_CAPACITY; i++){
        index = (index + i) % HASH_TABLE_CAPACITY;
    }
    if(i < HASH_TABLE_CAPACITY){
        ht->data[index].is_ocupied = 0;
        ht->size--;
    }

#elif defined(USE_QUADRATIC_PROBE)
    unsigned int c1 = 3;
    unsigned int c2 = 5;
    int i = 0;
    for(; ht->data[index].key != key && i < HASH_TABLE_CAPACITY; i++){
        index = (index + (c1 * i) + (c2 * i * i)) % HASH_TABLE_CAPACITY;
    }
    if(i < HASH_TABLE_CAPACITY)
        ht->data[index].is_ocupied = 0;
#endif
    
}

int ht_open_addr_get(HashTableOpenAddressing *ht, unsigned int key, int *value){
#if defined(USE_DIVISION_HASH)
    unsigned int index = hash_division(key, HASH_TABLE_CAPACITY); 
#elif defined(USE_MULTIPLICATION_HASH)
    unsigned int index = hash_multiplication(key, HASH_TABLE_CAPACITY);
#else
    unsigned int index = hash_universal(index, HASH_TABLE_CAPACITY);
#endif

#if defined(USE_LINEAR_PROBE)
    int i = 0;
    for(; ht->data[index].key != key && i < HASH_TABLE_CAPACITY; i++){
        index = (index + i) % HASH_TABLE_CAPACITY;
    }
    if(i < HASH_TABLE_CAPACITY){
        *value = ht->data[index].value;
        return 1;
    }

#elif defined(USE_QUADRATIC_PROBE)
    unsigned int c1 = 3;
    unsigned int c2 = 5;
    int i = 0;
    for(; ht->data[index].key != key && i < HASH_TABLE_CAPACITY; i++){
        index = (index + (c1 * i) + (c2 * i * i)) % HASH_TABLE_CAPACITY;
    }
    if(i < HASH_TABLE_CAPACITY){
        *value = ht->data[index].value;
        return 1;
    }
#endif
    return 0;
}


void ht_chaining_init(HashTableChaining *ht){
    srand(time(NULL));
    memset(ht, 0,sizeof(*ht));
}

void ht_chaining_display(HashTableChaining *ht){
    for(int i = 0; i < HASH_TABLE_CAPACITY; i++){
        printf("[%02d]->", i);
        if(ht->data[i]){
            ChainSlot *cur = ht->data[i];
            while(cur){
                printf("[ %02d | %02d ]->", cur->key, cur->value);
                cur = cur->next;
            }
        }
        printf("[ null ]");
        printf("\n");
    }
}

void ht_chaining_insert(HashTableChaining *ht, unsigned int key, int value){
    if(ht->size == HASH_TABLE_CAPACITY)
        return;
#if defined(USE_DIVISION_HASH)
    unsigned int index = hash_division(key, HASH_TABLE_CAPACITY); 
#elif defined(USE_MULTIPLICATION_HASH)
    unsigned int index = hash_multiplication(key, HASH_TABLE_CAPACITY);
#else
    unsigned int index = hash_universal(index, HASH_TABLE_CAPACITY);
#endif
    
    ChainSlot *slot = calloc(1, sizeof(*slot));
    slot->key = key;
    slot->value = value;
    if(ht->data[index]){
        slot->next = ht->data[index];        
    }
    ht->data[index] = slot;
    ht->size++;
}

void ht_chaining_delete(HashTableChaining *ht, unsigned int key){
#if defined(USE_DIVISION_HASH)
    unsigned int index = hash_division(key, HASH_TABLE_CAPACITY); 
#elif defined(USE_MULTIPLICATION_HASH)
    unsigned int index = hash_multiplication(key, HASH_TABLE_CAPACITY);
#else
    unsigned int index = hash_universal(index, HASH_TABLE_CAPACITY);
#endif

    if(ht->data[index]){
        ChainSlot *cur = ht->data[index];
        ChainSlot *prev = NULL;
        while(cur && cur->key != key){
            prev = cur;
            cur = cur->next;
        }
        if(cur){
            if(prev){
                prev->next = cur->next;
                free(cur);
            }else{
                ht->data[index] = NULL;
            }
        }
    } 

}

int ht_chaining_get(HashTableChaining *ht, unsigned int key, int *value){
#if defined(USE_DIVISION_HASH)
    unsigned int index = hash_division(key, HASH_TABLE_CAPACITY); 
#elif defined(USE_MULTIPLICATION_HASH)
    unsigned int index = hash_multiplication(key, HASH_TABLE_CAPACITY);
#else
    unsigned int index = hash_universal(index, HASH_TABLE_CAPACITY);
#endif

    if(ht->data[index]){
        ChainSlot *slot = ht->data[index];
        while(slot->next && slot->next->key != key)
            slot = slot->next;
        if(slot){
            *value = slot->value;
            return 1;
        }
    }

    return 0;
}



int main(int argc, char *argv[])
{
    // ------------ OPEN ADDRESS HASH TABLE ------------ //
    printf("Open addressing hash table\n\n");
    HashTableOpenAddressing ht;
    ht_open_addr_init(&ht);

    ht_open_addr_display(&ht);

    ht_open_addr_insert(&ht, string_to_key("key1"), 10);
    ht_open_addr_insert(&ht, string_to_key("key2"), 9);
    ht_open_addr_insert(&ht, string_to_key("key3"), 8);
    ht_open_addr_insert(&ht, string_to_key("key4"), 7);
    ht_open_addr_insert(&ht, string_to_key("key5"), 6);
    ht_open_addr_insert(&ht, string_to_key("key6"), 5);
    ht_open_addr_insert(&ht, string_to_key("key7"), 4);
    ht_open_addr_insert(&ht, string_to_key("key8"), 3);
    ht_open_addr_insert(&ht, string_to_key("key9"), 2);
    ht_open_addr_insert(&ht, string_to_key("key10"), 1);

    ht_open_addr_display(&ht);

    ht_open_addr_delete(&ht, string_to_key("key6"));

    ht_open_addr_display(&ht);

    ht_open_addr_insert(&ht, string_to_key("key11"), -1);

    ht_open_addr_display(&ht);

    int value = 0;
    if(ht_open_addr_get(&ht, string_to_key("key4"), &value)){
        printf("value: %d\n", value);
    }


    if(!ht_open_addr_get(&ht, string_to_key("key100"), &value)){
        printf("key not found!\n");
    }

    // ------------ CHAINING HASH TABLE ------------ //
    printf("\n");
    printf("chainig hash table\n\n");
    HashTableChaining cht;
    ht_chaining_init(&cht);

    ht_chaining_display(&cht);
    printf("\n");

    ht_chaining_insert(&cht, string_to_key("key1"), 10);
    ht_chaining_insert(&cht, string_to_key("key2"), 9);
    ht_chaining_insert(&cht, string_to_key("key3"), 8);
    ht_chaining_insert(&cht, string_to_key("key4"), 7);
    ht_chaining_insert(&cht, string_to_key("key5"), 6);
    ht_chaining_insert(&cht, string_to_key("key6"), 5);
    ht_chaining_insert(&cht, string_to_key("key7"), 4);
    ht_chaining_insert(&cht, string_to_key("key8"), 3);
    ht_chaining_insert(&cht, string_to_key("key9"), 2);
    ht_chaining_insert(&cht, string_to_key("key10"), 1);

    ht_chaining_display(&cht);
    printf("\n");

    ht_chaining_delete(&cht, string_to_key("key6"));

    ht_chaining_display(&cht);
    printf("\n");

    ht_chaining_insert(&cht, string_to_key("key11"), -1);

    ht_chaining_display(&cht);

    value = 0;
    if(ht_chaining_get(&cht, string_to_key("key4"), &value)){
        printf("value: %d\n", value);
    }


    if(!ht_chaining_get(&cht, string_to_key("key100"), &value)){
        printf("key not found!\n");
    }

    return 0;
}

