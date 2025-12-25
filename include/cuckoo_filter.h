#ifndef CUCKOO_FILTER_H
#define CUCKOO_FILTER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define DEFAULT_BUCKET_DEPTH 4 // common b value used in Cuckoo filters to achieve a value of 95% load factor before insertions fail
#define DEFAULT_FINGERPRINT_BIT_COUNT 7 // ideal f value used in the original paper
#define OPTIMAL_LOAD_FACTOR 0.95
#define MAX_KICK_COUNT 500

typedef struct {
    uint32_t* buckets; // assuming a 7 bit fingerprint for 4 slots each, 32 bits can store all fingerprints
    size_t occupiedCount; // used for calculating 
    size_t bucketCount; // also known as m 
    size_t bucketDepth; // the number of fingerprints per bucket known as b
    size_t keySize; // bit count for fingerprints also known as f 
} CuckooFilter;

CuckooFilter* cf_create(unsigned int expectedElementCount);
bool cf_get_str(CuckooFilter* filter, const char* key);
bool cf_get_chr(CuckooFilter* filter, char key);
bool cf_get_int(CuckooFilter* filter, int key);
int cf_set_str(CuckooFilter* filter, const char* key);
int cf_set_chr(CuckooFilter* filter, char key);
int cf_set_int(CuckooFilter* filter, int key);
int cf_remove_str(CuckooFilter* filter, const char* key);
int cf_remove_chr(CuckooFilter* filter, char key);
int cf_remove_int(CuckooFilter* filter, int key);
int cf_free(CuckooFilter* filter);

#endif
