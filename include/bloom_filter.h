#ifndef Bloom_Filter_H
#define Bloom_Filter_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BYTE_SIZE 8

typedef struct {
    unsigned char* buckets;
    size_t totalBitCount; // total bit count / m value in bloom filters
    int hashFunctionCount; // k value in bloom filters
} BloomFilter;

/**
 * Instantiate a new bloom filter 
 * @param expectedElementCount number of unique elements the filter expects to hold (n value)
 * @param typeSize size in byte of the data to be stored
 */
BloomFilter* bf_create_fixed(unsigned int expectedElementCount);

int bf_get(const void* key);
int bf_set(const void* key);
int bf_free(void);

#endif