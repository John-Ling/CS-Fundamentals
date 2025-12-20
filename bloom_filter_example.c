#include <stdio.h>
#include <stdlib.h>

#include "bloom_filter.h"

int main(void) 
{
    BloomFilter* filter = LibBloomFilter.create(10);;
    // LibBloomFilter.set_str(filter, "Test");

    // printf("%d \n", LibBloomFilter.get_str(filter, "Test"));
    // printf("%d \n", LibBloomFilter.get_str(filter, "Not here"));

    LibBloomFilter.set_chr(filter, 'A');
    LibBloomFilter.set_chr(filter, 'B');
    LibBloomFilter.set_chr(filter, 'C');

    printf("%d \n", LibBloomFilter.get_chr(filter, 'A'));
    printf("%d \n", LibBloomFilter.get_chr(filter, 'B'));
    printf("%d \n", LibBloomFilter.get_chr(filter, 'D'));

    LibBloomFilter.free(filter);
    return EXIT_SUCCESS;
}
