#include "cuckoo_filter.h"

// Library implementing a bitpacked cuckoo filter for learning purposes 

static uint32_t _hash_string(const char* s);
static uint32_t _hash_int(int x);
static uint8_t _fingerprint(uint32_t hash, size_t fingerprintBitCount);
static int _find_open_bucket_slot(uint32_t bucket); 
static int _find_fingerprint(uint32_t bucket, uint8_t fingerprint);
static uint32_t _hash_fingerprint(uint8_t fingerprint);
static int _insert(CuckooFilter* filter, uint32_t h1);
static int _cuckoo_hashing(uint32_t* buckets, size_t bucketCount, uint32_t bucket1, 
						uint32_t bucket2, uint8_t fingerprint);
static bool _get(CuckooFilter* filter, uint32_t h1);
static int _remove(CuckooFilter* filter, uint32_t h1);

CuckooFilter* cf_create(unsigned int expectedElementCount)
{
	CuckooFilter* filter = malloc(sizeof(CuckooFilter));
	size_t bucketCount = ((expectedElementCount + DEFAULT_BUCKET_DEPTH - 1) / DEFAULT_BUCKET_DEPTH);
	filter->buckets = calloc(bucketCount, sizeof(uint32_t));
	filter->bucketCount = bucketCount;
	filter->storedFingerprintCount = 0;
	filter->bucketDepth = DEFAULT_BUCKET_DEPTH;
	filter->keySize = DEFAULT_FINGERPRINT_BIT_COUNT;

	srand(time(NULL));
	return filter;
}

int cf_set_str(CuckooFilter* filter, const char* key) 
{
	uint32_t h1 = _hash_string(key);
	return _insert(filter, h1);
}

bool cf_get_str(CuckooFilter* filter, const char* key)
{
	uint32_t h1 = _hash_string(key);
	return _get(filter, h1);
}

int cf_remove_str(CuckooFilter* filter, const char* key)
{
	uint32_t h1 = _hash_string(key);
	return _remove(filter, h1);
}

int cf_set_chr(CuckooFilter* filter, char key)
{
	uint32_t h1 = _hash_int(key);
	return _insert(filter, h1);
}

bool cf_get_chr(CuckooFilter* filter, char key)
{
	uint32_t h1 = _hash_int(key);
	return _get(filter, h1);
}

int cf_remove_chr(CuckooFilter* filter, char key)
{
	uint32_t h1 = _hash_int(key);
	return _remove(filter, h1);
}

int cf_set_int(CuckooFilter* filter, int key)
{
	uint32_t h1 = _hash_int(key);
	return _insert(filter, h1);
}

bool cf_get_int(CuckooFilter* filter, int key)
{
	uint32_t h1 = _hash_int(key);
	return _get(filter, h1);
}

int cf_remove_int(CuckooFilter* filter, int key)
{
	uint32_t h1 = _hash_int(key);
	return _remove(filter, h1);
}

int cf_free(CuckooFilter* filter)
{
	free(filter->buckets);
	filter->buckets = NULL;
	free(filter);
	filter = NULL;
	return EXIT_SUCCESS;
}

static int _insert(CuckooFilter* filter, uint32_t h1)
{
	uint32_t bucket1 = h1 % filter->bucketCount;
	uint8_t fingerprint = _fingerprint(bucket1, filter->keySize);
	uint32_t bucket2 = (bucket1 ^ _hash_fingerprint(fingerprint)) % filter->bucketCount;

	int offset1 = _find_open_bucket_slot(filter->buckets[bucket1]);
	int offset2 = _find_open_bucket_slot(filter->buckets[bucket2]);
	filter->storedFingerprintCount++;

	if (offset1 != -1) 
	{
		filter->buckets[bucket1] |= (uint32_t)fingerprint << offset1;
	}
	else if (offset2 != -1)
	{
		filter->buckets[bucket2] |= (uint32_t)fingerprint << offset2;
	}
	else 
	{
		_cuckoo_hashing(filter->buckets, filter->bucketCount, bucket1, bucket2, fingerprint);
	}
	return EXIT_SUCCESS;
}

static bool _get(CuckooFilter* filter, uint32_t h1)
{
	uint32_t bucket1 = h1 % filter->bucketCount;
	uint8_t fingerprint = _fingerprint(bucket1, filter->keySize);
	uint32_t bucket2 = (h1 ^ _hash_fingerprint(fingerprint)) % filter->bucketCount;

	if (_find_fingerprint(filter->buckets[bucket1], fingerprint) != -1 || 
		_find_fingerprint(filter->buckets[bucket2], fingerprint) != -1) 
	{
		return true;
	}
		
	return false;
}

static int _remove(CuckooFilter* filter, uint32_t h1)
{
	uint32_t bucket1 = h1 % filter->bucketCount;
	uint8_t fingerprint = _fingerprint(bucket1, filter->keySize);
	uint32_t bucket2 = (bucket1 ^ _hash_fingerprint(fingerprint)) % filter->bucketCount;

	int offset1 = _find_fingerprint(filter->buckets[bucket1], fingerprint);
	int offset2 = _find_fingerprint(filter->buckets[bucket2], fingerprint);

	if (offset1 != -1) 
	{
		filter->buckets[bucket1] &= ~(0xFFu << offset1);
		return EXIT_SUCCESS;
	}
	else if (offset2 != -1)
	{
		filter->buckets[bucket2] &= ~(0xFFu << offset2);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

static int _cuckoo_hashing(uint32_t* buckets, size_t bucketCount, uint32_t bucket1, 
						uint32_t bucket2, uint8_t fingerprint)
{
	uint32_t evict = (rand() % 2) ? bucket2 : bucket1;
	
	for (int i = 0; i < MAX_KICK_COUNT; i++) 
	{
		// find occupied slots
		int occupiedSlots[4];
		int occupiedCount = 0;
		for (int offset = 0; offset < 32; offset += 8) 
		{
			if ((buckets[evict] >> offset) & 0xFF) 
			{
				occupiedSlots[occupiedCount++] = offset;
			}
		}
		
		if (occupiedCount < 4) 
		{
			int emptyOffset = _find_open_bucket_slot(buckets[evict]);
			buckets[evict] |= (uint32_t)fingerprint << emptyOffset;
			return EXIT_SUCCESS;
		}
		
		// Randomly select from occupied slots
		int offset = occupiedSlots[rand() % occupiedCount];
		uint8_t evictedFingerprint = (buckets[evict] >> offset) & 0xFF;
		
		// Replace with new fingerprint
		buckets[evict] &= ~(0xFFu << offset);
		buckets[evict] |= (uint32_t)fingerprint << offset;
		
		// Try to place evicted fingerprint
		uint32_t newBucket = (evict ^ _hash_fingerprint(evictedFingerprint)) % bucketCount;
		int newOffset = _find_open_bucket_slot(buckets[newBucket]);
		
		if (newOffset != -1) {
			buckets[newBucket] |= (uint32_t)evictedFingerprint << newOffset;
			return EXIT_SUCCESS;
		}
		
		evict = newBucket;
		fingerprint = evictedFingerprint;
	}
	
	return EXIT_FAILURE;
}

static uint8_t _fingerprint(uint32_t hash, size_t fingerprintBitCount)
{
	uint8_t fingerprint = hash & ((1 << fingerprintBitCount) - 1);
	fingerprint += (fingerprint == 0); // ensure fingerprint is not 0
	return fingerprint;
}

/**
 * Magic number is derived from MurmurHash2
 */
static uint32_t _hash_fingerprint(uint8_t fingerprint)
{
	return fingerprint * 0x5bd1e995;
}

/**
 * Checks 1 byte sections within a bucket
 * A 0 value represents an empty space
 * Return the offset to the empty space
 * Returns -1 if all buckets slots are full
 */
static int _find_open_bucket_slot(uint32_t bucket) 
{
	for (int i = 0; i < 32; i += 8) 
	{
		if ((bucket & (0xFFu << i))  == 0) 
		{
			return i;
		}
		
	}

	return -1;
}

/**
 * Checks 1 byte sections within a bucket
 * and checks if they match the fingerprint
 * Returns ths offset to the nibble with the matching fingerprint
 * Returns -1 if fingerprint is not found
 */
static int _find_fingerprint(uint32_t bucket, uint8_t fingerprint)
{
	for (int i = 0; i < 32; i += 8) 
	{
		uint8_t byte = (bucket >> i) & 0xFFu;
		if (byte == fingerprint) return i;
	}

	return -1;
}

// djb2 hashing algorithm by Dan Bernstein
static uint32_t _hash_string(const char* s)
{
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

const struct LibCuckooFilter_l LibCuckooFilter = {
	.create = cf_create,
	.set_str = cf_set_str,
    .get_str = cf_get_str,
    .set_chr = cf_set_chr,
    .get_chr = cf_get_chr,
    .set_int = cf_set_int,
    .get_int = cf_get_int,
    .remove_str = cf_remove_str,
    .remove_chr = cf_remove_chr,
    .remove_int = cf_remove_int,
    .free = cf_free
};
