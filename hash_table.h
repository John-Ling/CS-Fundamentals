enum HashType
{
	STRING, 
	INT
};

typedef void* HashKey;
typedef void* HashValue;

typedef struct HashTable_t
{
	HashKey* keys; // array of keys
	HashValue* values; // array of values
	enum HashType keyType;
	enum HashType valueType;
	int size;
} HashTable;

HashTable* create_hash_table(const int keyOption, const int valueOption, const int size);
static int set_type(const int option, enum HashType* type);
static unsigned int hash(const char* s);
static unsigned int hash_num(unsigned int x);
// int division_hash(const int input);
// int mid_square_hash(const int input);
// int string_to_ascii(const char *str);
// int insert(Bucket hashTable[], const char* key, const char *value);
// char* retrieve(Bucket hashTable[], const char* key);
// int delete(Bucket hashTable[], const char* key);

// int (*hash_function)(int) = &mid_square_hash; // Change for different hash functions