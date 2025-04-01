#ifndef Hash_Table_H
#define Hash_Table_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
} HashTable;


HashTable* ht_create(HashType keyType, const int bucketCount, const size_t dataSize);
int ht_insert_str(HashTable* table, char* key, void* value);
int ht_insert_chr(HashTable* table, char key, void* value);
int ht_insert_int(HashTable* table, int key, void* value);
int ht_insert_flt(HashTable* table, float key, void* value);
int ht_insert_dbl(HashTable* table, double key, void* value);

// insert data into specific bucket (index) in hash table
// performs separate chaining to resolve collisions
static int ht_insert(HashTable* table, const index, void* value);
int ht_free(HashTable* table, void free_item(void*));

int ht_get_str(HashTable* table, const char* key, void* out);

static size_t set_type(HashType type);
static unsigned int hash_string(const char* s);
// static unsigned int hash_num(unsigned int x);

struct LibHashTable_l {
	// create a hash table
    HashTable* (*create)(HashType keyType, const int bucketCount, const size_t dataSize);
    int (*free)(HashTable* table, void free_item(void*));
};

extern const struct LibHashTable_l LibHashTable;
#endif