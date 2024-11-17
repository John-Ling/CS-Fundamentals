#include "linked_lists.h"

enum HashType
{
	STRING, 
	INT
};

typedef void* HashKey;
typedef void* HashValue;

// hash table that uses separate chaining to resolve collisions
typedef struct HashTable_t
{
	LinkedList* keys;
	LinkedList* values;
	enum HashType keyType;
	enum HashType valueType;
} HashTable;

HashTable* ht_create(const int keyOption, const int valueOption, const int size);
int ht_insert(HashTable* table, void* key, void* value);
int ht_free(HashTable* table);
static int set_type(const int option, enum HashType* type);
static unsigned int calc_hash(void* n, enum HashType type);
static unsigned int hash_string(const char* s);
static unsigned int hash_num(unsigned int x);