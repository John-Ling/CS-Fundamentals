#ifndef Hash_Table_H
#define Hash_Table_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "linked_lists.h"

// possible types that can be used as keys for 
// the hash table
typedef enum HashType_e
{
	STRING = 1, 
	INT,
	CHAR,
	DBL,
	FLT
} HashType;


// hash table that uses separate chaining to resolve collisions
typedef struct HashTable_t
{
	// hashable types are
	// string
	// char
	// int float double
	int bucketCount;
	LinkedList** buckets; // static sized array of linked lists
	HashType type; // specifies the data type used for a key
	size_t keySize;
	size_t dataSize;
} HashTable;

// key value pair
typedef struct KeyValue_t
{
	void* data;
	void* key;
} KeyValue;


HashTable* ht_create(HashType keyType, const int bucketCount, const size_t dataSize);
int ht_insert_str(HashTable* table, const char* key, void* value);
int ht_insert_chr(HashTable* table, char key, void* value);
int ht_insert_int(HashTable* table, int key, void* value);
int ht_insert_flt(HashTable* table, float key, void* value);
int ht_insert_dbl(HashTable* table, double key, void* value);


int ht_free(HashTable* table, void free_item(void*));
void* ht_get_str(HashTable* table, const char* key);
int ht_delete_str(HashTable* table, const char* key, void free_item(void*));

int ht_print_keys(HashTable* table, void print(const void*));

unsigned int hash_string(const char* s);

void ht_free_key_value_pair(void* pair);
// static unsigned int hash_num(unsigned int x);

struct LibHashTable_l {
	// create a hash table
    HashTable* (*create)(HashType keyType, const int bucketCount, const size_t dataSize);
    int (*free)(HashTable* table, void free_item(void*));

	int (*insert_str)(HashTable* table, const char* key, void* value);

	void* (*get_str)(HashTable* table, const char* key);

	
	int (*delete_str)(HashTable* table, const char* key, void free_item(void*));

	int (*print_keys)(HashTable* table, void print(const void*));
};

extern const struct LibHashTable_l LibHashTable;
#endif