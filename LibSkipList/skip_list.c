#include "skip_list.h"

SkipList *sl_create(void *values[], size_t n, size_t dataSize)
{
    if (values == NULL && n != 0)
    {
        return NULL;
    }

    srand(time(NULL));

    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    if (list == NULL)
    {
        return NULL;
    }

    list->dataSize = dataSize;
    list->height = 0;

    // for (int i = 0; i < _MAX_SKIP_LIST_LAYERS; i++)
    // {
    //     list->layers[i] = LibLinkedList.create(NULL, 0, sizeof(SkipListNode));
    // }

    return list;
}

void print_skip_list_node(const void* value) 
{
    SkipListNode* node = (SkipListNode*)value;
    printf("%d ", *(int*)node->value);
    return;
}

int sl_insert(SkipList *list, const void *value, int bigger(const void *, const void *))
{
    SkipListNode** createdNodes[_MAX_SKIP_LIST_LAYERS];

    int layerCount = 1;
    int promote = rand() % 2;

    // Flip a "coin" to determine whether to promote or the insert the node
    // Keep "coin flipping" to determine which layer the new node will exist on
    while (promote == 1 && layerCount <= _MAX_SKIP_LIST_LAYERS)
    {
        layerCount++;
        promote = rand() % 2;
    }

    // layerCount = 3;

    // insert node into N layers starting from the bottom
    for (int i = 0; i < layerCount; i++)
    {   
        if (list->layers[i] == NULL)
        {
            // create layer if one does not yet exist
            list->layers[i] = LibLinkedList.create(NULL, 0, sizeof(SkipListNode));
            list->height++;
        }

        int insertPosition = -1;
        int currentPosition = 0;
        LinkedList* layer = list->layers[i];
        ListNode* next = layer->head;

        while (next != NULL)
        {
            // go through layer until bigger value is reached
            int isBigger = bigger(((SkipListNode *)next->value)->value, value);
            if (isBigger == 1 || isBigger == 0)
            {
                // printf("Inserting into %d\n", currentPosition);
                insertPosition = currentPosition;
                break;
            }
            currentPosition++;
            next = next->next;
        }

        // create skip list node
        // ListNode* insertNode = _create_skip_list_node(value, list->dataSize);
        // SkipListNode* createdNode = (SkipListNode*)insertNode->value;

        SkipListNode* node = (SkipListNode*)malloc(sizeof(SkipListNode));

        node->value = (void**)malloc(sizeof(void*));
        node->below = NULL;

        memcpy(node->value, value, list->dataSize);

        ListNode* insertNode = _ll_create_node((void*)node, sizeof(SkipListNode));

        _ll_insert_node(list->layers[i], insertNode, insertPosition);
        // keep track of address of inserted node for connection later
        createdNodes[i] = &node;
    }

    
    // connect nodes together starting from top

    if (layerCount == 1) 
    {
        return EXIT_SUCCESS;
    }

    // printf("Printing current list\n");
    // printf("Layer count %d\n", layerCount);
    // printf("Insert nodes %d\n", nodeCount);

    for (int i = 0; i < layerCount; i++) 
    {
        ll_print(list->layers[i], print_skip_list_node);
    }

    // puts("Connecting");
    for (int i = layerCount - 1; i >= 1; i--) 
    {
        // printf("Connecting node %d with %d\n", i, i-1);
        if (createdNodes[i] == NULL || createdNodes[i - 1] == NULL) 
        {
            puts("NULL");
        }

        (*createdNodes[i])->below = (*createdNodes[i - 1]);
    }

    // puts("Done");

    return EXIT_SUCCESS;
}



ListNode* _create_skip_list_node(const void* value, size_t dataSize) 
{
    SkipListNode* node = (SkipListNode*)malloc(sizeof(SkipListNode));
    if (node == NULL)
    {
        return NULL;
    }

    node->value = (void**)malloc(sizeof(void*));
    node->below = NULL;
    if (node->value == NULL)
    {
        return NULL;
    }

    memcpy(node->value, value, dataSize);

    ListNode* insertNode = _ll_create_node((void*)node, sizeof(SkipListNode));
    if (insertNode == NULL)
    {
        return NULL;
    }
    return insertNode;
}


int sl_insert_int(SkipList *list, int value)
{
    return sl_insert(list, &value, bigger_int);
}

// int sl_search(SkipList* list, void* value, int compare(const void*, const void*))
// {
//     // iterate through skip list top layer
//     // check if
// }