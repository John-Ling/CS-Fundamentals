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
static inline size_t next_power_of_two (size_t x);
static bool _get(CuckooFilter* filter, uint32_t h1);
static int _remove(CuckooFilter* filter, uint32_t h1);

CuckooFilter* cf_create(unsigned int expectedElementCount)
{
	CuckooFilter* filter = malloc(sizeof(CuckooFilter));
	size_t bucketCount = (next_power_of_two(expectedElementCount / DEFAULT_BUCKET_DEPTH));
	
	filter->buckets = calloc(expectedElementCount, sizeof(uint32_t));
	filter->bucketCount = expectedElementCount;
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
	uint8_t fingerprint = _fingerprint(h1, filter->keySize);
	uint32_t bucket2 = (bucket1 ^ _hash_fingerprint(fingerprint)) % filter->bucketCount;

	int offset1 = _find_open_bucket_slot(filter->buckets[bucket1]);
	int offset2 = _find_open_bucket_slot(filter->buckets[bucket2]);

	if (offset1 != -1)
	{
		filter->storedFingerprintCount++;
		filter->buckets[bucket1] |= (uint32_t)fingerprint << offset1;
		return EXIT_SUCCESS;
	}
	else if (offset2 != -1)
	{
		filter->storedFingerprintCount++;
		filter->buckets[bucket2] |= (uint32_t)fingerprint << offset2;
		return EXIT_SUCCESS;
	}
	else
	{
		if (_cuckoo_hashing(filter->buckets, filter->bucketCount, bucket1, bucket2, fingerprint) == EXIT_SUCCESS)
		{
			filter->storedFingerprintCount++;
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}
}

static bool _get(CuckooFilter* filter, uint32_t h1)
{
	uint32_t bucket1 = h1 % filter->bucketCount;
	uint8_t fingerprint = _fingerprint(h1, filter->keySize);
	uint32_t bucket2 = (bucket1 ^ _hash_fingerprint(fingerprint)) % filter->bucketCount;

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
	uint8_t fingerprint = _fingerprint(h1, filter->keySize);
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
    uint32_t currentBucket = (rand() % 2) ? bucket2 : bucket1;

    for (int i = 0; i < MAX_KICK_COUNT; i++)
    {
        // Pick a random slot to evict
        int offset = (rand() % 4) * 8;  // 0, 8, 16, or 24

        uint8_t evicted = (buckets[currentBucket] >> offset) & 0xFF;

        // If slot is empty (fingerprint == 0), just insert here
        if (evicted == 0) {
            buckets[currentBucket] |= (uint32_t)fingerprint << offset;
            return EXIT_SUCCESS;
        }

        // Replace with current fingerprint
        buckets[currentBucket] &= ~(0xFFu << offset);
        buckets[currentBucket] |= (uint32_t)fingerprint << offset;

        // Now to relocate the evicted fingerprint
        currentBucket = (currentBucket ^ _hash_fingerprint(evicted)) % bucketCount;
        fingerprint = evicted;
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

static inline size_t next_power_of_two (size_t x) 
{
  --x;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16; 

  if (8 == sizeof(size_t)) {
    x |= x >> 32; 
  }

  return ++x;
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
