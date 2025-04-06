#include "hash_table.h"

// implementation of a basic hash table with separate chaining for learning purposes

// allocated 
// table
// buckets
// buckets for each index
// key value pair
// key value pair key and value

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

	table->keySize = set_type(keyType);
	table->dataSize = dataSize;

	// create buckets in hash table
	// generate static array
	table->buckets = (LinkedList**)malloc(sizeof(LinkedList*) * bucketCount);

	// populate array with linked lists
	for (int i = 0; i < bucketCount; i++)
	{
		// create linked list of key value structs
		table->buckets[i] = LibLinkedList.create(NULL, 0, sizeof(KeyValue));

		if (table->buckets[i] == NULL)
		{
			return NULL;
		}
	}

	return table;
}


int ht_free(HashTable* table, void free_item(void*))
{
	if (free_item == NULL)
	{
		free_item = default_free;
	}

    for (int i = 0; i < table->bucketCount; i++)
	{
		ht_free_bucket(table->buckets[i], free_item);
	}

	free(table->buckets);
	table->buckets = NULL;
	free(table);
	table = NULL;
	return EXIT_SUCCESS;
}

// modified version of the 
static int ht_free_bucket(LinkedList* list, void free_item(void*))
{
	if ((list)->head == NULL)
    {
        free(list);
        list = NULL;
        return EXIT_SUCCESS;
    }

    ListNode* previous = list->head;
	KeyValue* pair = (KeyValue*)previous->value;
    list->head = list->head->next;
    while (list->head != NULL)
    {
		// free key value pair
		free(pair->key);
		pair->key = NULL;
		free_item(pair->data);
		pair->data = NULL; 

		free_item(previous->value);
		previous->value = NULL;
        free(previous);
        previous = list->head;
		pair = (KeyValue*)list->head->value;
        list->head = list->head->next;
    }

	// free final
	free(pair->key);
	pair->key = NULL;
	free_item(pair->data);
	pair->data = NULL;

    free_item(previous->value);
	previous->value = NULL;
    free(previous);
    previous = NULL;
	free(list);
	(list) = NULL;
    return EXIT_SUCCESS;
}

int ht_insert_str(HashTable* table, const char* key, void* value) 
{
	// generate hash of string
	// try add to index
	// resolve collisions if needed
	const int index = hash_string(key) % table->bucketCount;
	return ht_insert(table, index, (void*)key, value);
}


int ht_insert(HashTable* table, const int index, void* key, void* value)
{
	// insert data into correct bucket
	// LibLinkedList.insert will insert data to the back of the list
	// making insertion super easy

	// create key value pair
	KeyValue* keyValuePair = (KeyValue*)malloc(sizeof(KeyValue));
	keyValuePair->data = (void**)malloc(sizeof(void*));
	memcpy(keyValuePair->data, value, table->dataSize);
	keyValuePair->key = (void**)malloc(sizeof(void*));
	memcpy(keyValuePair->key, value, table->keySize);

	int ret = LibLinkedList.insert(table->buckets[index], (void*)keyValuePair, -1);

	// linked list insert will create a new node and copy over 
	// the data via memcpy it has its own record of keyValuePair however the members key and data
	// are still in memory and still need to be used
	// the keyValuePair struct we initialised is not needed though so we free it
	free(keyValuePair);
	keyValuePair = NULL;
	return ret;
}

void* ht_get_str(HashTable* table, const char* key)
{
	// hash string to get index
	// check if index is not null
	// if not then traverse linked list until key is found 
	// return 0 if found 1 if not 
	const int index = hash_string(key) % table->bucketCount;

	if (table->buckets[index] == NULL)
	{
		puts("Null");
		return NULL;
	}

	ListNode* current = table->buckets[index]->head;
	
	// go through
	// linked list until 
	while (current != NULL)
	{
		KeyValue* pair = (KeyValue*)current->value;
		
		if (compare_str(pair->key, (void*)key) == EXIT_SUCCESS)
		{
			return pair->data;
		}
		current = current->next;
	}

	puts("Could not find ");
	return NULL;
}

// returns the correct memory size based on hash type
size_t set_type(HashType type)
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
unsigned int hash_string(const char* s)
{
	// hash(i - 1) * 33 ^ str[i];
	unsigned long hash = 5381;
	while (*s != NULL)	
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
    .free = ht_free,
	.insert_str = ht_insert_str,
	.get_str = ht_get_str
};