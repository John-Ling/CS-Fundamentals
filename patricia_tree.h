#ifndef Patricia_Tree_H
#define Patricia_Tree_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct PatriciaNode_t
{
    struct PatriciaNode_t* left; // next bit is 0
    struct PatriciaNode_t* right; // next bit is 1
    char* prefix; // binary prefix could use an unsigned int with 0b representation
    bool isTerminal; // if isTerminal is true then value will not be null
    char* value; // actual stored value 
} PatriciaNode;


/* Number of bits in a single character. */
#define BITS_PER_BYTE 8


int _find_bit_mismatch(char a, char b);
char* _find_bit_suffix(char int startBit);
char* _find_common_prefix(char* a, char* b);

int _editDistance(char *str1, char *str2, int n, int m);
int _min(int a, int b, int c);
/* Helper function. Gets the bit at bitIndex from the string s. */
int _getBit(char *s, unsigned int bitIndex);
char* _createStem(char *oldKey, unsigned int startBit, unsigned int numBits);

#endif 