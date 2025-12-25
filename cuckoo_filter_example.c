#include "cuckoo_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) 
{
    CuckooFilter* filter = LibCuckooFilter.create(10);
    LibCuckooFilter.set_str(filter, "A");
    LibCuckooFilter.set_str(filter, "Dog");
    LibCuckooFilter.set_str(filter, "Orangutan");
    LibCuckooFilter.set_str(filter, "Tide pods");
    LibCuckooFilter.set_str(filter, "Malaysia boleh");


    printf("%d\n", LibCuckooFilter.get_str(filter, "A"));
    printf("%d\n", LibCuckooFilter.get_str(filter, "Malaysia"));
    printf("%d\n", LibCuckooFilter.get_str(filter, "apple"));
    printf("%d\n", LibCuckooFilter.get_str(filter, "Orangutan"));

    cf_free(filter);
    return EXIT_SUCCESS;
}