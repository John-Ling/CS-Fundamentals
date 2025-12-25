#include "cuckoo_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) 
{
    CuckooFilter* filter = cf_create(10);
    cf_set_str(filter, "A");
    cf_set_str(filter, "banana");

    printf("%d\n", cf_get_str(filter, "A"));
    // printf("%d\n", cf_get_str(filter, "B"));
    printf("%d\n", cf_get_str(filter, "C"));
    // printf("%d\n", cf_get_str(filter, "D"));

    printf("%d\n", cf_get_str(filter, "apple"));
    printf("%d\n", cf_get_str(filter, "banana"));

    cf_free(filter);
    return EXIT_SUCCESS;
}