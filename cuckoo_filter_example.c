#include "cuckoo_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) 
{
    CuckooFilter* filter = cf_create(10);
    cf_set_str(filter, "A");
    cf_set_str(filter, "BA");
    cf_set_str(filter, "BC");
    cf_set_str(filter, "DS");
    cf_set_str(filter, "B");
    cf_set_str(filter, "bananan smoothie");
    cf_set_str(filter, "B");
    cf_set_str(filter, "bananan smoothie");
    cf_set_str(filter, "banana");

    printf("%d\n", cf_get_str(filter, "B"));
    printf("%d\n", cf_get_str(filter, "D"));

    printf("%d\n", cf_get_str(filter, "apple"));

    cf_free(filter);
    return EXIT_SUCCESS;
}