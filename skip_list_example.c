#include <stdio.h>
#include <stdlib.h>

#include "skip_list.h"

int main(void)
{
    SkipList* list = sl_create(NULL, 0, sizeof(int));

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", i);
        sl_insert_int(list, i);
    }
    

    return EXIT_SUCCESS;
}