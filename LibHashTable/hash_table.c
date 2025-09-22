#include "hash_table.h"

// implementation of a basic hash table with separate chaining for learning purposes

static int _ht_free_bucket(LinkedList* list, void free_item(void*));
static KeyValue* _ht_create_pair(const void* key, const void* value, size_t keySize, size_t valueSize);

// insert data into specific bucket (index) in hash table
// performs separate chaining to resolve collisions
static int _ht_insert(HashTable* table, int index, KeyValue* pair);
static int _ht_delete(HashTable* table, const void* key, int index, void free_item(void*),
			int compare_key(const void* a, const void* b));
size_t _set_type(HashType type);
static unsigned int _ht_hash_string(const char* s);
static unsigned int _ht_hash_int(int x);
static int _compare_pair_int(const void* _pair, const void* _key);
static int _compare_pair_str(const void* _pair, const void* _key);
static KeyValue* _ht_get(LinkedList* bucket, const void* key, int (*compare)(const void *, const void *));


// creates a hash table
HashTable* ht_create(HashType keyType, const int bucketCount, const size_t dataSize)
{
	HashTable* table = (HashTable* )malloc(sizeof(HashTable));
	if (table == NULL)
	{
		return NULL;
	}

	// set type
	table->type = keyType;
	table->bucketCount = bucketCount;

	table->keySize = _set_type(keyType);
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

int ht_insert_str(HashTable* table, const char* key, const void* value)
{
	// get length of string
	const char* s = key;
	const int index = _ht_hash_string(key) % table->bucketCount;

	// check if already exists update it 
	KeyValue* _exist = ht_get_str(table, key);
	if (_exist != NULL)
	{
		_exist->data = memcpy(_exist->data, value, table->dataSize);
		return EXIT_SUCCESS;
	}

	KeyValue* pair = _ht_create_pair(key, value, strlen(key) + 1, table->dataSize);

	// use hidden method to directly insert pair
	_ht_insert(table, index, pair);
	free(pair);
	pair = NULL;
	return EXIT_SUCCESS;
}

int ht_insert_int(HashTable* table, int key, const void* value)
{
	int bucketIndex = _ht_hash_int(key) % table->bucketCount;

	KeyValue* _exist = ht_get_int(table, key);
	if (_exist != NULL)
	{
		_exist->data = memcpy(_exist->data, value, table->dataSize);
		return EXIT_SUCCESS;
	}

	KeyValue* pair = _ht_create_pair(&key, value, sizeof(int), table->dataSize);


	_ht_insert(table, bucketIndex, pair);
	free(pair);
	pair = NULL;
	return EXIT_SUCCESS;
}

int ht_insert_chr(HashTable* table, char key, const void* value)
{
	int bucketIndex = _ht_hash_int((int)key) % table->bucketCount;

	KeyValue* _exist = ht_get_int(table, (int)key);
	if (_exist != NULL)
	{
		_exist->data = memcpy(_exist->data, value, table->dataSize);
		return EXIT_SUCCESS;
	}

	KeyValue* pair = _ht_create_pair(&key, value, sizeof(char), table->dataSize);
	
	_ht_insert(table, bucketIndex, pair);
	free(pair);
	pair = NULL;
	return EXIT_SUCCESS;
}

static int _ht_insert(HashTable* table, const int index, KeyValue* pair)
{
	return LibLinkedList.insert(table->buckets[index], (void*)pair, -1);
}

static int _compare_pair_str(const void* _pair, const void* _key)
{
	KeyValue* pair = (KeyValue*)_pair;
	return compare_str(pair->key, _key);
}

static int _compare_pair_int(const void* _pair, const void* _key)
{
	KeyValue* pair = (KeyValue*)_pair;
	int* key =  (int*)_key; 
	return compare_int(pair->key, key);
}

KeyValue* ht_get_str(HashTable* table, const char* key)
{
	// hash string to get index
	const int index = _ht_hash_string(key) % table->bucketCount;

	if (table->buckets[index] == NULL)
	{
		return NULL;
	}

	LinkedList* bucket = table->buckets[index];
	return _ht_get(bucket, key, _compare_pair_str);
}

KeyValue* ht_get_int(HashTable* table, int key)
{
	int index = _ht_hash_int(key) % table->bucketCount;

	if (table->buckets[index] == NULL)
	{
		return NULL;
	}
	LinkedList* bucket = table->buckets[index];
	return _ht_get(bucket, &key, _compare_pair_int);
}

KeyValue* ht_get_chr(HashTable* table, char key)
{
	return ht_get_int(table, (int)key);
}

static KeyValue* _ht_get(LinkedList* bucket, const void* key, int (*compare)(const void *, const void *))
{
	KeyValue* ret = (KeyValue*)LibLinkedList.search(bucket, key, compare);
	return ret;
}

static int _ht_delete(HashTable* table, const void* key, int index, void free_item(void*),
					int compare_key(const void* a, const void* b))
{
	if (free_item == NULL)
	{
		free_item = free;
	}

	if (compare_key == NULL)
	{
		return EXIT_FAILURE;
	}

	LinkedList* list = table->buckets[index];
	ListNode* current = list->head;
	ListNode* previous = current;

	if (list->head == NULL)
	{
		return EXIT_FAILURE;
	}

	// handle case where only 1 item is in list
	if (list->itemCount == 1) 
	{
		KeyValue* pair = (KeyValue*)current->value;
		// check 
		if (compare_key(pair->key, key) == EXIT_FAILURE)
		{
			return EXIT_FAILURE;
		}

		list->itemCount = list->itemCount - 1;

		
		free_item(pair->data);
		pair->data = NULL;
		free(pair->key);
		pair->key = NULL;

		free(current->value);
		current->value = NULL;
		free(current);
		current = NULL;
		list->head = NULL;
		return EXIT_SUCCESS;
	}

	int found = 0;
	current = current->next;
	while (current != NULL)
	{
		// go through linked list until either end is reached
		// or key match is found
		KeyValue* pair = (KeyValue*)current->value;

		if (compare_key(pair->key, key) == EXIT_SUCCESS)
		{
			found = 1;
			break;
		}
		previous = current;
		current = current->next;
	}

	if (found == 0)
	{
		return EXIT_FAILURE;
	}

	list->itemCount = list->itemCount - 1;
	// attach pointer
	previous->next = current->next;


	KeyValue* pair = (KeyValue*)current->value;
	free_item(pair->data);
	pair->data = NULL;
	free(pair->key);
	pair->key = NULL;
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;

    return EXIT_SUCCESS;
}

int ht_delete_str(HashTable* table, const char* key, void free_item(void*))
{
	int index = _ht_hash_string(key) % table->bucketCount;
	return _ht_delete(table, key, index, free_item, compare_str);
}

int ht_delete_int(HashTable* table, int key, void free_item(void*))
{
	int bucketIndex = _ht_hash_int(key) % table->bucketCount;
	return _ht_delete(table, &key, bucketIndex, free_item, compare_int);
}

int ht_delete_chr(HashTable* table, char key, void free_item(void*))
{
	return ht_delete_int(table, (int)key, free_item);
}

int ht_free(HashTable* table, void free_item(void*))
{
	if (free_item == NULL)
	{
		free_item = free;
	}

	for (int i = 0; i < table->bucketCount; i++)
	{
		_ht_free_bucket(table->buckets[i], free_item);
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
static int _ht_free_bucket(LinkedList* list, void free_item(void*))
{
	if ((list)->head == NULL)
	{
		free(list);
		list = NULL;
		return EXIT_SUCCESS;
	}

	ListNode* previous = list->head;
	KeyValue* pair = (KeyValue* )previous->value;

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
		pair = (KeyValue* )list->head->value;
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

int ht_print_keys(HashTable* table, void print(const void*))
{
	for (int i = 0; i < table->bucketCount; i++)
    {
        if (table->buckets[i]->head == NULL)
        {
            puts("NOTHING HERE");
            continue;
        }
        LibLinkedList.print(table->buckets[i], print);
    }
	return EXIT_SUCCESS;
}

static KeyValue* _ht_create_pair(const void* key, const void* value, size_t keySize, 
								size_t valueSize)
{
	KeyValue* pair = (KeyValue*)malloc(sizeof(KeyValue));
	if (pair == NULL)
	{
		return NULL;
	}

	pair->data = (void*)malloc(valueSize);
	pair->key = (void*)malloc(keySize);

	if (pair->data == NULL || pair->key == NULL)
	{
		free(pair);
		pair = NULL;
		return NULL;
	}

	memmove(pair->data, value, valueSize);
	memmove(pair->key, key, keySize);

	return pair;
}

// returns the correct memory size based on hash type
size_t _set_type(HashType type)
{
	switch (type)
	{
	case 1:
		return sizeof(char*);
	case 2:
		return sizeof(int);
	case 3:
		return sizeof(char);
	default:
		return -1;
	}
}

// djb2 hashing algorithm by Dan Bernstein
static unsigned int _ht_hash_string(const char* s)
{
	// hash(i - 1) * 33 ^ str[i];
	unsigned long hash = 5381;
	while (*s)
	{
		hash = hash * 33 ^ *s;
		s++;
	}
	return hash;
}

static unsigned int _ht_hash_int(int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

const struct LibHashTable_l LibHashTable = {
	.create = ht_create,
	.free = ht_free,
	.insert_str = ht_insert_str,
	.insert_int = ht_insert_int,
	.insert_chr = ht_insert_chr,
	.get_str = ht_get_str,
	.get_int = ht_get_int,
	.get_chr = ht_get_chr,
	.delete_str = ht_delete_str,
	.delete_int = ht_delete_int,
	.delete_chr = ht_delete_chr,
	.print_keys = ht_print_keys
};
