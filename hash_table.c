#include "hash_table.h"

// implementation of a basic hash table with separate chaining for learning purposes

// creates a hash table 
HashTable* ht_create(HashType keyType, const int bucketCount, const size_t dataSize)
{
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	if (table == NULL)
	{
		return NULL;
	}

	// set type
	table->type= keyType;
	table->bucketCount = bucketCount;

	// create buckets in hash table
	// generate static array
	table->buckets = (LinkedList**)malloc(sizeof(LinkedList*) * bucketCount);

	// populate array with linked lists
	for (int i = 0; i < bucketCount; i++)
	{
		table->buckets[i] = LibLinkedList.create(NULL, 0, dataSize);
		if (table->buckets[i] == NULL)
		{
			return NULL;
		}
	}

	return table;
}

int ht_free(HashTable* table, void free_item(void*))
{
	for (int i = 0; i < table->bucketCount; i++) 
	{
		LibLinkedList.free(table->buckets[i], free_item);
	}

	free(table->buckets);
	table->buckets = NULL;
	free(table);
	table = NULL;
	return EXIT_SUCCESS;
}

// inserts a key and value pair into the hash table
// int ht_insert(HashTable* table, void* key, void* value)
// {
	// calculate hash depending on datatype of key
	// unsigned int hash = calc_hash(key, table->keyType) % table->size;

	// // write value to values in table
	// if (table->keys[hash] != NULL)
	// {
	// 	// value already inserted
	// 	// resolve conflicts using either 
	// 	// open addressing or chaining`

	// 	puts("key already in hash table");
	// 	return EXIT_FAILURE;
	// }

	// if (table->values[hash] != NULL)
	// {
	// 	puts("value already in hash table");
	// 	return EXIT_FAILURE;
	// }

	// table->keys[hash] = key;
	// table->values[hash] = value;
	
// 	return EXIT_SUCCESS;
// }

// hash table helper functions

// handles collisions in the hash table using separate chaining
// static int handle_collision(HashTable* table, void* item, const int index)
// {
// 	return 0;
// }

// returns the correct memory size based on hash type
static size_t set_type(HashType type)
{
	switch(type)
	{
		case 1:
			return sizeof(char*);
		case 2:
			return sizeof(int);
		case 3:
			return sizeof(char);
		case 4:
			return sizeof(double);
		case 5:
			return sizeof(float);
		default:
			return -1;
	}
}

// calculate the hash of a generic value n
// static unsigned int calc_hash(void* n, enum HashType type)
// {
// 	unsigned int hash;
// 	if (type == STRING)
// 	{
// 		char* _n = n;
// 		hash = hash_string(_n);
// 	}
// 	else if (type == INT)
// 	{
// 		int* _n = n;
// 		hash = hash_num(*_n);
// 	}
// 	return hash;
// }

// static unsigned int hash_string(const char* s)
// {
// 	unsigned int x = 0;
// 	while (*s)
// 	{
// 		x += (int)*s;
// 		s++;
// 	}

// 	return hash_num(x);
// }

// static unsigned int hash_num(unsigned int x)
// {
// 	x = ((x >> 16) ^ x) * 0x45d9f3b;
//     x = ((x >> 16) ^ x) * 0x45d9f3b;
//     x = (x >> 16) ^ x;
//     return x % 100;
// }

const struct LibHashTable_l LibHashTable = {
    .create = ht_create,
    .free = ht_free
};