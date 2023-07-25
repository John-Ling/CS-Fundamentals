#include <stdio.h>
#include <math.h>

// implementation of a hash table with linear probing for learning purposes

#define BUCKET_COUNT 30

struct bucket_data_t 
{
	char* data;
	char* key;
};
typedef struct bucket_data_t bucket_data;

int division_hash(int input);
int mid_square_hash(int input);
int string_to_ascii_value(char *str);
int insert(char* key, char *value);
char* retrieve(char* key);

bucket_data hashTable[BUCKET_COUNT];
int (*hash_function)(int) = &mid_square_hash; // Change for different hash functions

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

// Returns the middle r digits from the square of the input
int mid_square_hash(int input) 
{
	const int r = 1; // Get the middle r digits in the square of the input

	int hash = 0;
	int square = pow(input, 2);
	int digitCount = 1;
	int multiplier = 10;

	while ((int)(square / multiplier) != 0) // Count digits
	{
		digitCount++;
		multiplier *= 10;
	}

	int digits[digitCount];
	for (int i = digitCount - 1; i >= 0; i--)
	{
		digits[i] = square % 10;
		square = (int)(square / 10);
	}

	int start = (int)(digitCount / 2);
	if (digitCount % 2 == 0)
	{
		start--; // In an even number of digits with a pair of values, we start at the left value i.e we start at 2 in 23
	}

	multiplier = 1;
	for (int i = start + r - 1; i >= start; i--)
	{
		hash += digits[i] * multiplier;
		multiplier *= 10;
	}

	return hash;
}