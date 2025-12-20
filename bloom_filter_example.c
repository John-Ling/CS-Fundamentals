#include <stdio.h>
#include <stdlib.h>
#include "bloom_filter.h"

int main(void) {
    BloomFilter* filter = bf_create_fixed(10);
    return EXIT_SUCCESS;
}