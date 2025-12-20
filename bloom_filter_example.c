#include <stdio.h>
#include <stdlib.h>

#include "bloom_filter.h"

int main(void) 
{
    BloomFilter* filter = LibBloomFilter.create(10);;
    LibBloomFilter.set_str(filter, "Test");

    printf("%d \n", LibBloomFilter.get_str(filter, "Test"));
    printf("%d \n", LibBloomFilter.get_str(filter, "Not here"));
    return EXIT_SUCCESS;
}