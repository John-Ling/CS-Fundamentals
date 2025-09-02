#ifndef Patricia_Trie_H
#define Patricia_Trie_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


// node can either be 2 types
// terminal node which stores a value
// or a internal node which joins the tree together
// a leaf node will have no children
typedef struct PatriciaNode_t
{
    struct PatriciaNode_t* left; // next bit is 0
    struct PatriciaNode_t* right; // next bit is 1
    int prefixBitCount; // maybe include 
    char* prefix; // binary prefix will not always be a printable string due to potential missing null terminator watch out!
    int instances; // handle duplicate by storing the number of times they occur
    char* value; // actual stored value present if node is a terminal/leaf node 
} PatriciaNode;

/* Number of bits in a single character. */
#define BITS_PER_BYTE 8

PatriciaNode* pt_create(char* value);
PatriciaNode* _pt_create_node(void);
PatriciaNode* pt_insert(PatriciaNode* root, char* value, int valueBitCount);

int bitwiseStrcmp(char* a, char*  b, int* totalComparisons);
int _find_bit_mismatch(char* a, char* b, int bitCountA, int bitCountB);
char* _find_bit_suffix(char* key, int startBit);
char* _find_common_prefix(char* a, char* b);

int _editDistance(char *str1, char *str2, int n, int m);
int _min(int a, int b, int c);
/* Helper function. Gets the bit at bitIndex from the string s. */
int _getBit(char *s, unsigned int bitIndex);
char* _createStem(char *oldKey, unsigned int startBit, unsigned int numBits);

#endif 