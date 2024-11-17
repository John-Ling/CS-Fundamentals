#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"

// implementation of a basic hash table with linear probing for learning purposes

int main(void)
{
	// Bucket hashTable[BUCKET_COUNT];

	// for (int i = 0; i < BUCKET_COUNT; i++)
	// {
	// 	hashTable[i].key = NULL; // Initialise hash table
	// 	hashTable[i].removed = 0;
	// }

	// insert(hashTable, "Batman", "Josh");
	// insert(hashTable, "atmaBn", "Joshy");
	// retrieve(hashTable, "Batman");
	// retrieve(hashTable, "atmaBn");

	// delete(hashTable, "atmaBn");
	// retrieve(hashTable, "Batman");
	// retrieve(hashTable, "atmaBn");

	// const char* str = "hello";
	// printf("%lu\n", hash(str, strlen(str)));
	// str = "hello!";
	// printf("%lu\n", hash(str, strlen(str)));

	HashTable* table = ht_create(1, 2, 30);

	int key = 34;
	char* value = "234";
	ht_insert(table, &key, &value);
	
	return EXIT_SUCCESS;
}

// creates a hash table with a certain key and value type determined by
// 1: STRING
// 2: INT
HashTable* ht_create(const int keyOption, const int valueOption)
{
	if (keyOption < 0 || valueOption < 0)
	{
		return NULL;
	}

	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	if (table == NULL)
	{
		return NULL;
	}

	// create types
	enum HashType keyType;
	enum HashType valueType;

	if (set_type(keyOption, &keyType) || set_type(valueOption, &valueType))
	{
		return NULL;
	}
	table->keyType = keyType;
	table->valueType = valueType;

	// create value and key arrays
	table->keys = (LinkedList*)malloc(sizeof(LinkedList));
	if (table->keys == NULL)
	{
		return NULL;
	}

	table->values = (LinkedList*)malloc(sizeof(LinkedList));
	if (table->values == NULL)
	{
		return NULL;
	}

	return table;
}

int ht_free(HashTable* table)
{
	free(table->keys);
	table->keys = NULL;
	free(table->values);
	table->values = NULL;
	free(table);
	table = NULL
	return EXIT_SUCCESS;
}

// inserts a key and value pair into the hash table
int ht_insert(HashTable* table, void* key, void* value)
{
	// calculate hash depending on datatype of key
	unsigned int hash = calc_hash(key, table->keyType) % table->size;

	// write value to values in table
	if (table->keys[hash] != NULL)
	{
		// value already inserted
		// resolve conflicts using either 
		// open addressing or chaining`

		puts("key already in hash table");
		return EXIT_FAILURE;
	}

	if (table->values[hash] != NULL)
	{
		puts("value already in hash table");
		return EXIT_FAILURE;
	}

	table->keys[hash] = key;
	table->values[hash] = value;
	
	return EXIT_SUCCESS;
}

// hash table helper functions

// handles collisions in the hash table using separate chaining
static int handle_collision(HashTable* table, void* item, const int index)
{
	
}

// sets type based on option determined by
// 1: STRING
// 2: INT
static int set_type(const int option, enum HashType* type)
{
	switch (option)
	{
		case 1:
			*type = STRING;
			break;
		case 2:
			*type = INT;
			break;
		default:
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// calculate the hash of a generic value n
static unsigned int calc_hash(void* n, enum HashType type)
{
	unsigned int hash;
	if (type == STRING)
	{
		char* _n = n;
		hash = hash_string(_n);
	}
	else if (type == INT)
	{
		int* _n = n;
		hash = hash_num(*_n);
	}
	return hash;
}

static unsigned int hash_string(const char* s)
{
	unsigned int x = 0;
	while (*s)
	{
		x += (int)*s;
		s++;
	}

	return hash_num(x);
}

static unsigned int hash_num(unsigned int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % 100;
}