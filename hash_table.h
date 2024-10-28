#define BUCKET_COUNT 30

typedef struct
{
	char* data;
	char* key;
	bool removed;
} Bucket;

int division_hash(const int input);
int mid_square_hash(const int input);
int string_to_ascii(const char *str);
int insert(Bucket hashTable[], const char* key, const char *value);
char* retrieve(Bucket hashTable[], const char* key);
int delete(Bucket hashTable[], const char* key);

int (*hash_function)(int) = &mid_square_hash; // Change for different hash functions