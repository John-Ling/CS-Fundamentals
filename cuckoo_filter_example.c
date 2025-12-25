#include "cuckoo_filter.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    CuckooFilter* filter = cf_create(10);
    return EXIT_SUCCESS;
}