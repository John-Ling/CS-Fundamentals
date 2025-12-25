#include "cuckoo_filter.h"

// Library implementing a cuckoo filter for learning purposes 

static uint32_t _hash_string(const char* s);
static uint32_t _hash_int(int x);
static uint8_t _fingerprint(uint32_t hash, size_t fingerprintBitCount);
static int _find_open_bucket_slot(uint32_t bucket); 

CuckooFilter* cf_create(unsigned int expectedElementCount) 
{
	CuckooFilter* filter = malloc(sizeof(CuckooFilter));
	filter->buckets = malloc(sizeof(uint32_t*) * expectedElementCount);
	filter->bucketCount = expectedElementCount;
	filter->bucketDepth = DEFAULT_BUCKET_DEPTH;
	filter->keySize = DEFAULT_FINGERPRINT_BIT_COUNT;

	srand(time(NULL));
	return filter;
}

int cf_set_str(CuckooFilter* filter, const char* key) 
{
	uint32_t bucket1 = _hash_string(key) ;
	unsigned char fingerprint = _fingerprint(bucket1, filter->keySize);

	// hash the fingerprint using murmurhash's constant to approximate the hash
	uint32_t bucket2 = bucket1 ^ (fingerprint * 0x5bd1e995); // magic number derived from murmurhash

	bucket1 = bucket1 % filter->bucketCount;
	bucket2 = bucket2 % filter->bucketCount;

	int offset1 = _find_open_bucket_slot(filter->buckets[bucket1]);
	int offset2 = _find_open_bucket_slot(filter->buckets[bucket2]);
	if (offset1 != -1) 
	{
		filter->buckets[bucket1] |= (uint32_t)fingerprint << offset1;
		return EXIT_SUCCESS;
	}
	else if (offset2 != -1)
	{
		filter->buckets[bucket2] |= (uint32_t)fingerprint << offset2;
		return EXIT_SUCCESS;
	}

	// Both slots are occupied
	puts("Both slots are full");

	uint32_t evict;
	switch (rand() % 2)
	{
		case 0: 
			evict = bucket1;
			break;
		case 1: 
			evict = bucket2;
			break;
	}

	for (int i = 0; i < MAX_KICK_COUNT; i++) 
	{
		// Select a random slot from bucket	
		int offset = -1;
		switch (rand() % 4) 
		{
			case 0: 
				offset = 0;
				break;
			case 1: 
				offset = 4;
				break;
			case 2: 
				offset = 8;
				break;
			case 3: 
				offset = 12;
				break;
		}

		if (offset == -1) 
		{
			return EXIT_FAILURE;
		}

		// Evict stored fingerprint and store the new one in its place
		uint8_t evictedFingerprint = filter->buckets[evict] & (0xFu << offset);
		filter->buckets[evict] |= (uint32_t)fingerprint << offset;

		// find a new space to place evicted fingerprint
		uint32_t newBucket = evict ^ (fingerprint * 0x5bd1e995);
		int newOffset = _find_open_bucket_slot(filter->buckets[newBucket]);
		if (newOffset != -1) 
		{
			filter->buckets[evict] |= (uint32_t)evictedFingerprint << offset;
			return EXIT_SUCCESS;
		}
	}

	puts("Failed to write");
	return EXIT_FAILURE;
}

static uint8_t _fingerprint(uint32_t hash, size_t fingerprintBitCount)
{
	uint8_t fingerprint = hash & ((1 << fingerprintBitCount) - 1);
	fingerprint += (fingerprint == 0); // ensure fingerprint is never 0
	return fingerprint;
}

/**
 * Checks 4 bits within a bucket
 * A 0 value represents an empty space
 * Return the offset to the empty space
 * Returns -1 if all buckets slots are full
 */
static int _find_open_bucket_slot(uint32_t bucket) 
{
	if ((bucket & (0xFu << 0))  == 0) return 0;
	if ((bucket & (0xFu << 4))  == 0) return 4;
	if ((bucket & (0xFu << 8))  == 0) return 8;
	if ((bucket & (0xFu << 12)) == 0) return 12;
	return -1;
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
