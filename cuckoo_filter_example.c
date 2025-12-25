#include "cuckoo_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) 
{
    CuckooFilter* filter = cf_create(10);
    cf_set_str(filter, "A");
    cf_set_str(filter, "B");
    cf_set_str(filter, "C");
    return EXIT_SUCCESS;
}