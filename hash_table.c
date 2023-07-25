#include <stdio.h>

#define BUCKET_COUNT 30

struct bucket_data_t 
{
	char* data;
	char* key;
};
typedef struct bucket_data_t bucket_data;

int division_hash(int input);
int string_to_ascii_value(char *str);
int insert(char* key, char *value);
char* retrieve(char* key);

bucket_data hashTable[BUCKET_COUNT];
int (*hash_function)(int) = &division_hash; // Change for different hash functions

int main(void)
{
	for (int i = 0; i < BUCKET_COUNT; i++)
	{
		hashTable[i].key = NULL; // Initialise hash table
	}
	
	insert("Batman", "Josh");
	insert("atmaBn", "Joshy");
	printf("%s\n", retrieve("Batman"));
	printf("%s\n", retrieve("atmaBn"));

	return 0;
}

int string_to_ascii_value(char *str)
{
	int sum = 0;
	while (*str != '\0')
	{
		sum += (int)(*str);
		str++;
	}
	return sum;
}

int insert(char* key, char *value)
{
	int ascii = string_to_ascii_value(key);
	int hash = hash_function(ascii);

	if (hashTable[hash].key == NULL)
	{
		hashTable[hash].key = key;
		hashTable[hash].data = value;
	}
	else
	{
		// Perform linear probing to find an open space
		int index = hash + 3;
		while (index < BUCKET_COUNT) 
		{
			if (hashTable[index].key == NULL)
			{
				hashTable[index].key = key;
				hashTable[index].data = value;
				return 0;
			}
			index += 3;
		}
	}

	return 1;
}

char* retrieve(char* key)
{
	int ascii = string_to_ascii_value(key);
	int hash = hash_function(ascii);

	if (hashTable[hash].key == NULL)
	{
		printf("Key does not exist in map\n");
		return "\0";
	}
	
	if (hashTable[hash].key == key)
	{
		return hashTable[hash].data;
	}

	// Perform linear probing to find the correct key
	int index = hash + 3;
	while (index < BUCKET_COUNT)
	{
		if (hashTable[index].key == key)
		{
			return hashTable[index].data;
		}
		index += 3;
	}

	return "\0";
}

// Hash Functions

int division_hash(int input)
{
	return input % BUCKET_COUNT;
}

int mid_square_hash(int input) 
{
	int square = input^2;
	
	const int r = 2;
	return 0;
}