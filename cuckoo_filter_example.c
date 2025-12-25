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

    printf("%d\n", cf_get_str(filter, "A"));
    printf("%d\n", cf_get_str(filter, "B"));
    printf("%d\n", cf_get_str(filter, "C"));
    printf("%d\n", cf_get_str(filter, "D"));

    cf_remove_str(filter, "B");
    printf("%d\n", cf_get_str(filter, "B"));

    return EXIT_SUCCESS;
}