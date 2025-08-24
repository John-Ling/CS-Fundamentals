#include <stdio.h>
#include <stdlib.h>

#include "skip_list.h"

void print_skip_list_node(const void* value) 
{
    SkipListNode* node = (SkipListNode*)value;
    printf("%d ", *(int*)node->value);
    return;
}

int main(void)
{
    SkipList* list = sl_create(NULL, 0, sizeof(int));

    for (int i = 10; i >= 0; i--)
    {
        sl_insert_int(list, i);
    }

    // check if layers are connected
    printf("%p\n", ((SkipListNode*)((ListNode*)list->layers[list->layerCount - 1]->head->value)->value)->below);
    
    // 
    printf("%p\n",   ((SkipListNode*)((ListNode*)list->layers[0]->head->value)->value)->below);

    return EXIT_SUCCESS;
}