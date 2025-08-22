#include "skip_list.h"

SkipList* sl_create(void* values[], size_t n, size_t dataSize)
{
    if (values == NULL && n != 0) 
    {
        return NULL;
    }

    srand(time(NULL));
    
    SkipList* list = (SkipList*)malloc(sizeof(SkipList));
    if (list == NULL)
    {
        return NULL;
    }

    list->dataSize = dataSize;
    list->layerCount = 1;

    for (int i = 0; i < _MAX_SKIP_LIST_LAYERS; i++)
    {
        list->layers[i] = LibLinkedList.create(NULL, 0, sizeof(SkipListNode));
    }

    return list;
}

int sl_insert(SkipList* list, const void* value, int bigger(const void*, const void*))
{
    // puts("Inserting value");
    SkipListNode* createdNodes[_MAX_SKIP_LIST_LAYERS];
    int nodeCount = 0;

    int layerCount = 1;
    int promote = rand() % 2;


    // Flip a "coin" to determine whether to promote or the insert the node
    // Keep "coin flipping" to determine which layer the new node will exist on
    while (promote == 1 && layerCount <= _MAX_SKIP_LIST_LAYERS) 
    {
        layerCount++;
        promote = rand() % 2;
    }
    
    // insert node into N layers starting from the bottom
    for (int i = 0; i < layerCount; i++)
    {
        // perform sorted insert into linked list
        if (list->layers[i] == NULL)
        {
            // create layer if one does not yet exist
            list->layers[i] = LibLinkedList.create(NULL, 0, sizeof(SkipListNode));
        }

        int insertPosition = -1;
        int currentPosition = 0;
        LinkedList* layer = list->layers[i];
        ListNode* next = layer->head;

        while (next != NULL)
        {   
            // go through layer until bigger value is reached
            int isBigger = bigger(((SkipListNode*)next->value)->value, value );
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
        SkipListNode* node = (SkipListNode*)malloc(sizeof(SkipListNode));
        if (node == NULL)
        {
            return EXIT_FAILURE;
        }
        
        node->value = (void**)malloc(sizeof(void*));
        if (node->value == NULL) 
        {
            return EXIT_FAILURE;
        }

        memcpy(node->value, value, list->dataSize);

        ListNode* insertNode = _ll_create_node((void*)node, sizeof(SkipListNode));
        if (insertNode == NULL)
        {
            // add memory freeing code here
            return EXIT_FAILURE;
        }

        _ll_insert_node(list->layers[i], insertNode, insertPosition);

        // keep track of address of inserted node for connection later
        createdNodes[nodeCount] = node;
        nodeCount++;
    }
    // connect nodes together
    for (int i = layerCount - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            createdNodes[i]->below = NULL;
            continue;
        }

        createdNodes[i]->below = createdNodes[i - 1];
    }
    return EXIT_SUCCESS;
}

int sl_insert_int(SkipList* list, int value)
{
    return sl_insert(list, &value, bigger_int);
}

// int sl_search(SkipList* list, void* value, int compare(const void*, const void*)) 
// {
//     // iterate through skip list top layer 
//     // check if 
// }