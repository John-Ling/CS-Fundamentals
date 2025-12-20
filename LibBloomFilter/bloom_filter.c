#include "bloom_filter.h"

// library implementing a standard bloom filter for learning purposes

static void set_bit(unsigned char* s, size_t sBitCount, int index, unsigned char value);
static unsigned char get_bit(unsigned char* s, size_t sBitCount,  int index);

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

static void set_bit(unsigned char* s, size_t sBitCount, int index, unsigned char value) 
{
    if (index < 0  || index >= sBitCount) 
    {
        return;
    }

    int _index = index / BYTE_SIZE;
    int offset = index % BYTE_SIZE;

    switch(value)
    {
        case 0:
            s[_index] &= ~(1 << offset);
            break;
        case 1:
            s[_index] |= (1 << offset);
            break; 
    }

    return;
}

static unsigned char get_bit(unsigned char* s, size_t sBitCount, int index) 
{
    if (index < 0  || index >= sBitCount) 
    {
        return -1;
    }

    int _index = index / BYTE_SIZE;
    int offset = index % BYTE_SIZE;

    return (s[_index] & (1 << offset)) != 0;
}