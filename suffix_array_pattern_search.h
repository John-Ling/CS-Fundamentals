typedef struct 
{
    char* suffix;
    int startIndex;
} Suffix;

int generate_suffixes(int suffixArray[], const char* string);
int suffix_search(char* string, const char* pattern, int suffixArray[], const int n);
static int compare_suffixes(const void* a, const void* b);