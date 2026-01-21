#include "cuckoo_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) 
{
    CuckooFilter* filter = LibCuckooFilter.create(40);
    for (char c = 'a'; c <= 'z'; c++) {
        LibCuckooFilter.set_chr(filter, c);
    }

    for (char c = 'a'; c <= 'z'; c++)
    {
        printf("%d\n", LibCuckooFilter.get_chr(filter, c));
    }

    cf_free(filter);
    return EXIT_SUCCESS;
}