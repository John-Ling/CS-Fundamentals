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
    puts("Inserting into skip list");
    SkipListNode* createdNodes[_MAX_SKIP_LIST_LAYERS];
    int nodeCount = 0;

    int layerCount = 1;
    int promote = rand() % 2;

    puts("Promoting");
    printf("%d\n", promote);

    // Flip a "coin" to determine whether to promote or the insert the node
    // Keep "coin flipping" to determine which layer the new node will exist on
    while (promote == 1 && layerCount <= _MAX_SKIP_LIST_LAYERS) 
    {
        layerCount++;
        promote = rand() % 2;
        printf("%d\n", promote);
        puts("Promoting");
    }
    

    puts("Done");
    puts("Adding ");
    

    // insert node into N layers starting from the bottom
    for (int i = 0; i < layerCount; i++)
    {
        // sorted insert into linked list
        if (list->layers[i] == NULL)
        {
            puts("Creating layer");
            // create layer if one does not yet exist
            list->layers[i] = LibLinkedList.create(NULL, 0, sizeof(SkipListNode));
        }
        
        int insertPosition = -1;
        int currentPosition = 0;
        LinkedList* layer = list->layers[i];
        ListNode* next = layer->head;

        puts("Moving through");
        while (next != NULL)
        {   
            puts("Comparing");
            // go through layer until bigger value is reached
            int isBigger = bigger(next->value, value);
            if (isBigger == 1 || isBigger == 0)
            {
                insertPosition = currentPosition;
                break;
            }
            currentPosition++;
            next = next->next;
        }


        puts("creating node");
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

        puts("calling _ll_create_node");

        ListNode* insertNode = _ll_create_node(node, sizeof(SkipListNode));
        puts("Created");
        if (insertNode == NULL)
        {
            // add memory freeing code here
            return EXIT_FAILURE;
        }
        

        puts("Inserting node");
        _ll_insert_node(list->layers[i], insertNode, insertPosition);

        // keep track of address of inserted node for connection later
        createdNodes[nodeCount] = node;
        nodeCount++;
    }


    puts("Connecting nodes");
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