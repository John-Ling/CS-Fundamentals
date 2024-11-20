#include "linked_lists.h"

typedef enum
{
	STRING, 
	INT,
	CHAR
} HashType;


// hash table that uses separate chaining to resolve collisions
typedef struct HashTable_t
{
	LinkedList* keys;
	LinkedList* values;
	HashType type;
} HashTable;

HashTable* ht_create(const int keyOption, const int valueOption, const int size);
int ht_insert(HashTable* table, void* key, void* value);
int ht_free(HashTable* table);
static int set_type(const int option, HashType* type);
static unsigned int hash_string(const char* s);
static unsigned int hash_num(unsigned int x);