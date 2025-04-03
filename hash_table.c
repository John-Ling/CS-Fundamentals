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

int ht_insert_str(HashTable* table, const char* key, void* value) 
{
	// generate hash of string
	// try add to index
	// resolve collisions if needed

	const int index = hash_string(key) % table->bucketCount;
	return ht_insert(table, index, value);
}

int ht_get_str(HashTable* table, const char* key, void* out)
{
	// hash string to get index
	// check if index is not null
	// if not then traverse linked list until key is found 
	// return 0 if found 1 if not 
	const int index = hash_string(key) % table->bucketCount;

	if (table->buckets[index] == NULL)
	{
		return EXIT_FAILURE;
	}	

	

	return EXIT_SUCCESS;
}

static int ht_insert(HashTable* table, const index, void* value)
{
	// insert data into correct bucket
	// LibLinkedList.insert will insert data to the back of the list
	// making insertion super easy
	return LibLinkedList.insert(table->buckets[index], value, -1);
}


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


// djb2 hashing algorithm by Dan Bernstein
static unsigned int hash_string(const char* s)
{
	// hash(i - 1) * 33 ^ str[i];
	unsigned long hash = 5381;
	while (s != NULL)	
	{
		hash = hash * 33 ^ *s; /* hash * 33 + c */
		s++;
	}
	return hash;
}

static unsigned int hash_num(unsigned int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % 100;
}

const struct LibHashTable_l LibHashTable = {
    .create = ht_create,
    .free = ht_free
};