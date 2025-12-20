#include "bloom_filter.h"

// library implementing a standard bloom filter for learning purposes

BloomFilter* bf_create_fixed(unsigned int expectedElementCount) 
{
    if (expectedElementCount <= 0) {
        return NULL;
    }

    BloomFilter* filter = malloc(sizeof(BloomFilter));
    const int n = expectedElementCount;
    if (filter == NULL) {
        return NULL;
    }

    // assume a p value of 0.001 or 0.1%
    const double p = 0.001;

    // bit size of filter
    const int m = (int)round(-(n * log(p) / (pow(log(2), 2))));
    const int k = (int)round(m/n * log(2));

    filter->buckets = calloc((int)round(m / BYTE_SIZE) + BYTE_SIZE, sizeof(unsigned char));
    filter->hashFunctionCount = k;
    filter->totalBitCount = m;
    
    return filter;
}
