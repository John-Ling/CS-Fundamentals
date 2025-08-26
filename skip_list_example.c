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

    for (int i = list->height - 1; i >= 0 ; i--) 
    {
        ll_print(list->layers[i], print_skip_list_node);
    }

    // check if layers are connected
    LinkedList* firstLayer = list->layers[0];
    LinkedList* secondLayer = list->layers[1];
    LinkedList* thirdLayer = list->layers[2];

    // ll_print(firstLayer, print_skip_list_node);
    // ll_print(secondLayer, print_skip_list_node);
    SkipListNode* firstHead = (SkipListNode*)firstLayer->head->value;
    SkipListNode* secondHead = (SkipListNode*)secondLayer->head->value;
    SkipListNode* thirdHead = (SkipListNode*)thirdLayer->head->value;
    

    printf("Below 1st layer%p\n", (void*)firstHead->below );
    printf("below 2nd layer %p\n", (void*)secondHead->below);
    printf("Below 3rd layer %p\n", (void*)thirdHead->below);
    printf("Two layers below third %p\n", (void*)thirdHead->below->below->below);

    return EXIT_SUCCESS;
}