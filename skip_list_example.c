#include <stdio.h>
#include <stdlib.h>

#include "skip_list.h"

void print_skip_list_node(const void* value) 
{
    SkipListNode* node = (SkipListNode*)value;
    printf("%d ", *(int*)node->value);
    return;
}

void free_skip_list_node(void* value)
{
    SkipListNode* node = (SkipListNode*)value;
    free(node->value);
    node->value = NULL;
    free(node);
    node = NULL;
    return;
}

int main(void)
{
    SkipList* list = sl_create(NULL, 0, sizeof(int));

    for (int i = 10; i >= 0; i--)
    {
        sl_insert_int(list, i);
    }

    sl_insert_int(list, 13);
    sl_insert_int(list, 4);

    for (int i = list->height - 1; i >= 0 ; i--) 
    {
        ll_print(list->layers[i], print_skip_list_node);
    }

    printf("Search for 4 %d\n", sl_search_int(list, 4));
    printf("Search for 8 %d\n", sl_search_int(list, 8));
    printf("Search for 2 %d\n", sl_search_int(list, 2));
    printf("Search for 1 %d\n", sl_search_int(list, 1));

    printf("Search for 30 %d\n", sl_search_int(list, 30));
    printf("Search for -1 %d\n", sl_search_int(list, -1));
    printf("Search for 600 %d\n", sl_search_int(list, 600)); 

    sl_free(list, free_skip_list_node);

    return EXIT_SUCCESS;
}