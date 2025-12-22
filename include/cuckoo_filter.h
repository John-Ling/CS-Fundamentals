#ifndef Cuckoo_Filter_H
#define Cuckoo_Filter_H
#include <stdlib.h>

typedef struct {
    void** buckets;
    size_t bucketCount;
    size_t keySize; // fingerprint size in bits
} CuckooFilter;

typedef struct {
    unsigned char* key;
    void* value;
} Fingerprint;

#endif
