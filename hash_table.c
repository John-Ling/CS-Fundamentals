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

int ht_insert_str(HashTable* table, const char* key, void* value) 
{
	// get length of string
	char* s = key;
    int length = 0;
    while (*s)
    {
        s++;
        length++;
    }
	
	const int index = hash_string(key) % table->bucketCount;
	KeyValue* pair = __ht_create_pair(key, value, sizeof(char) * length, table->dataSize);

	// use hidden method to directly insert pair
	__ht_insert(table, index, pair);
	free(pair);
	return EXIT_SUCCESS;
}

int ht_insert(HashTable* table, const int index, void* key, void* value)
{
	// create key value pair
	KeyValue* keyValuePair = __ht_create_pair(key, value, table->keySize, table->dataSize);
	printf("%s\n", (char*)keyValuePair->key);
	int ret = LibLinkedList.insert(table->buckets[index], (void*)keyValuePair, -1);

	// linked list insert will create a new node and copy over 
	// the data via memcpy it has its own record of keyValuePair however the members key and data
	// are still in memory and still need to be used
	// the keyValuePair struct we initialised is not needed though so we free it
	free(keyValuePair);
	keyValuePair = NULL;
	return ret;
}

static int __ht_insert(HashTable* table, const int index, KeyValue* pair)
{
	return LibLinkedList.insert(table->buckets[index], (void*)pair, -1);
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

int ht_free(HashTable* table, void free_item(void*))
{
	if (free_item == NULL)
	{
		free_item = default_free;
	}

    for (int i = 0; i < table->bucketCount; i++)
	{
		__ht_free_bucket(table->buckets[i], free_item);
	}

	free(table->buckets);
	table->buckets = NULL;
	free(table);
	table = NULL;
	return EXIT_SUCCESS;
}

// modified version of the linked list free
// function but adapted to expect KeyValue structs
// whilst allowing the use of a user defined free function
static int __ht_free_bucket(LinkedList* list, void free_item(void*))
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
	list = NULL;
    return EXIT_SUCCESS;
}


static KeyValue* __ht_create_pair(void* key, void* value, size_t keySize, size_t valueSize)
{
	KeyValue* pair = (KeyValue*)malloc(sizeof(KeyValue));
	if (pair == NULL)
	{
		return NULL;
	}

	pair->data = (void**)malloc(sizeof(void*));
	pair->key = (void**)malloc(sizeof(void*));

	if (pair->data == NULL || pair->key == NULL)
	{
		free(pair);
		pair = NULL;
		return NULL;
	}

	memcpy(pair->data, value, valueSize);
	memcpy(pair->key, key, keySize);

	return pair;
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