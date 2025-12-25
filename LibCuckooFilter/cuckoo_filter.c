#include "cuckoo_filter.h"

// Library implementing a cuckoo filter for learning purposes 

static uint32_t _hash_string(const char* s);
static uint32_t _hash_int(int x);
static unsigned char _fingerprint(uint32_t hash, size_t fingerprintBitCount);

CuckooFilter* cf_create(unsigned int expectedElementCount) 
{
	CuckooFilter* filter = malloc(sizeof(CuckooFilter));
	filter->buckets = malloc(sizeof(uint32_t*) * expectedElementCount);
	filter->bucketCount = expectedElementCount;
	filter->bucketDepth = DEFAULT_BUCKET_DEPTH;
	filter->keySize = DEFAULT_FINGERPRINT_BIT_COUNT;
	return filter;
}

int cf_set_str(CuckooFilter* filter, const char* key) 
{
	uint32_t h1 = _hash_string(key) ;
	unsigned char fingerprint = _fingerprint(h1, filter->keySize);

	// hash the fingerprint using murmurhash's constant to approximate the hash
	uint32_t h2 = h1 ^ (fingerprint * 0x5bd1e995); // magic number derived from murmurhash

	h1 = h1 % filter->bucketCount;
	h2 = h2 % filter->bucketCount;

	printf("%d %d\n", h1, h2);
	return EXIT_SUCCESS;
}

static unsigned char _fingerprint(uint32_t hash, size_t fingerprintBitCount)
{
	unsigned char fingerprint = ((1 << fingerprintBitCount) - 1);
	fingerprint += (fingerprint == 0); // ensure fingerprint is never 0
	return fingerprint;
}

// djb2 hashing algorithm by Dan Bernstein
static uint32_t _hash_string(const char* s)
{
	// hash(i - 1) * 33 ^ str[i];
	unsigned long hash = 5381;
	while (*s)
	{
		hash = hash * 33 ^ *s;
		s++;
	}
	return hash;
}

static uint32_t _hash_int(int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}
