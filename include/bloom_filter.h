#ifndef Bloom_Filter_H
#define Bloom_Filter_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define BYTE_SIZE 8
#define SALT 0x9e3779b97f4a7c15ULL

typedef struct {
    unsigned char* buckets;
    size_t totalBitCount; // total bit count / m value in bloom filters
    size_t hashFunctionCount; // k value in bloom filters
} BloomFilter;

BloomFilter* bf_create_fixed(unsigned int expectedElementCount);
bool bf_get_str(BloomFilter* filter, const char* key);
bool bf_get_chr(BloomFilter* filter, char key);
bool bf_get_int(BloomFilter* filter, int key);
int bf_set_str(BloomFilter* filter, const char* key);
int bf_set_chr(BloomFilter* filter, char key);
int bf_set_int(BloomFilter* filter, int key);
int bf_free(void);

struct LibBloomFilter_l {
    /**
     * Instantiate a new bloom filter 
     * @param expectedElementCount number of unique elements the filter expects to hold (n value)
     * @param typeSize size in byte of the data to be stored
     */
    BloomFilter* (*create)(unsigned int expectedElementCount);
    int (*set_str)(BloomFilter* filter, const char* key);
    int (*set_chr)(BloomFilter* filter, char key);
    int (*set_int)(BloomFilter* filter, int key);   

    bool (*get_str)(BloomFilter* filter, const char* key);
    bool (*get_chr)(BloomFilter* filter, char key);
    bool (*get_int)(BloomFilter* filter, int key);
};

extern const struct LibBloomFilter_l LibBloomFilter;
#endif