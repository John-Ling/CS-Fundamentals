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

	HashTable* table = create_hash_table(1, 2, 30);

	const char* str = "hello";
	printf("%u\n", hash(str));
	str = "hell";
	printf("%u\n", hash(str));
	return EXIT_SUCCESS;
}


// creates a hash table with a certain key and value type determined by
// 1: STRING
// 2: INT
HashTable* create_hash_table(const int keyOption, const int valueOption, const int size)
{
	if (keyOption < 0 || valueOption < 0)
	{
		return NULL;
	}

	enum HashType keyType;
	enum HashType valueType;

	if (set_type(keyOption, &keyType) || set_type(valueOption, &valueType))
	{
		return NULL;
	}

	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	if (table == NULL)
	{
		return NULL;
	}

	table->keyType = keyType;
	table->valueType = valueType;
	table->size = size;
	return table;
}

int table_insert()


// hash table helper functions

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

static unsigned int hash(const char* s)
{
	unsigned int x = 0;
	while (*s)
	{
		x += (int)*s;
		*s++;
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

// int string_to_ascii(const char *str)
// {
// 	int sum = 0;
// 	while (*str != '\0')
// 	{
// 		sum += (int)(*str);
// 		str++;
// 	}
// 	return sum;
// }

// int insert(Bucket hashTable[], const char* key, const char *value)
// {
// 	int ascii = string_to_ascii(key);
// 	int hash = hash_function(ascii);

// 	if (hashTable[hash].key == NULL)
// 	{
// 		printf("Inserting data\n");
// 		hashTable[hash].key = (char*)key;
// 		hashTable[hash].data = (char*)value;
// 		return EXIT_SUCCESS;
// 	}

// 	if (hashTable[hash].key == key) // Item is already present in hash table
// 	{
// 		printf("Item already exists in table");
// 		return EXIT_SUCCESS;
// 	}

// 	// Perform linear probing to find an open space
// 	int index = hash + 3;
// 	while (index < BUCKET_COUNT) 
// 	{
// 		if (hashTable[index].key == NULL)
// 		{
// 			printf("Inserting data\n");
// 			hashTable[index].key = (char*)key;
// 			hashTable[index].data = (char*)value;
// 			return EXIT_SUCCESS;
// 		}
// 		index += 3;
// 	}

// 	printf("Could not insert data");
// 	return EXIT_FAILURE;
// }

// char* retrieve(Bucket hashTable[], const char* key)
// {
// 	int ascii = string_to_ascii(key);
// 	int hash = hash_function(ascii);

// 	if (hashTable[hash].key == NULL)
// 	{
// 		printf("Could not retrieve key");
// 		return NULL;
// 	}
	
// 	if (hashTable[hash].key == key && hashTable[hash].removed == 0)
// 	{
// 		printf("%s\n", hashTable[hash].data);
// 		return hashTable[hash].data;
// 	}

// 	// Perform linear probing to find the correct key
// 	int index = hash + 3;
// 	while (index < BUCKET_COUNT)
// 	{
// 		if (hashTable[index].key == key && hashTable[index].removed == 0)
// 		{
// 			printf("%s\n", hashTable[index].data);
// 			return hashTable[index].data;
// 		}
// 		index += 3;
// 	}

// 	printf("Could not retrieve key\n");
// 	return NULL;
// }

// int delete(Bucket hashTable[], const char* key)
// {
// 	int ascii = string_to_ascii(key);
// 	int hash = hash_function(ascii);

// 	if (hashTable[hash].key == NULL)
// 	{
// 		printf("Key provided does not exist in table");
// 		return EXIT_FAILURE;
// 	}

// 	if (hashTable[hash].removed)
// 	{
// 		return EXIT_SUCCESS;
// 	}

// 	if (hashTable[hash].key == key)
// 	{
// 		hashTable[hash].removed = 1;
// 		return EXIT_SUCCESS;
// 	}

// 	int index = hash + 3;
// 	while (index < BUCKET_COUNT)
// 	{
// 		if (hashTable[index].removed)
// 		{
// 			return EXIT_SUCCESS;
// 		}

// 		if (hashTable[index].key == key)
// 		{
// 			hashTable[index].removed = 1;
// 			return EXIT_SUCCESS;
// 		}
// 	}

// 	printf("Could not find key");
// 	return EXIT_FAILURE;
// }

// // Hash Functions

// int division_hash(const int input)
// {
// 	return input % BUCKET_COUNT;
// }

// // Returns the middle r digits from the square of the input
// int mid_square_hash(int input) 
// {
// 	const int r = 1; // Get the middle r digits in the square of the input

// 	int hash = 0;
// 	int square = pow(input, 2);
// 	int digitCount = 1;
// 	int multiplier = 10;

// 	while ((int)(square / multiplier) != 0) // Count digits
// 	{
// 		digitCount++;
// 		multiplier *= 10;
// 	}

// 	int digits[digitCount];
// 	for (int i = digitCount - 1; i >= 0; i--)
// 	{
// 		digits[i] = square % 10;
// 		square = (int)(square / 10);
// 	}

// 	int start = (int)(digitCount / 2);
// 	if (digitCount % 2 == 0)
// 	{
// 		// In an even number of digits with a pair of values, 
// 		// we start at the left value i.e we start at 2 in 23
// 		start--; 
// 	}

// 	multiplier = 1;
// 	for (int i = start + r - 1; i >= start; i--)
// 	{
// 		hash += digits[i] * multiplier;
// 		multiplier *= 10;
// 	}

// 	return hash;
// }