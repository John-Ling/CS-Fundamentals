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
    LinkedList* firstLayer = list->layers[0];
    LinkedList* secondLayer = list->layers[1];

    // ll_print(firstLayer, print_skip_list_node);
    // ll_print(secondLayer, print_skip_list_node);
    SkipListNode* firstHead = (SkipListNode*)firstLayer->head->value;
    SkipListNode* secondHead = (SkipListNode*)secondLayer->head->value;
    

    printf("%p\n", (void*)firstHead->below );
    printf("%p\n", (void*)secondHead->below);

    return EXIT_SUCCESS;
}