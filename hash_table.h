#define BUCKET_COUNT 30

struct bucket_data_t 
{
	char* data;
	char* key;
	_Bool removed;
};
typedef struct bucket_data_t bucket_data;

int division_hash(int input);
int mid_square_hash(int input);
int string_to_ascii(char *str);
int insert(char* key, char *value);
char* retrieve(char* key);
int delete(char* key);

bucket_data hashTable[BUCKET_COUNT];
int (*hash_function)(int) = &mid_square_hash; // Change for different hash functions