#include "skip_list.h"

// library for a skip list of any type created for learning purposes

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

int sl_insert(SkipList *list, const void *value, int bigger(const void*, const void*))
{
    int layerCount = 1;
    int promote = rand() % 2;

    // Flip a "coin" to determine whether to promote or the insert the node
    // Keep "coin flipping" to determine which layer the new node will exist on
    while (promote == 1 && layerCount <= _MAX_SKIP_LIST_LAYERS)
    {
        layerCount++;
        promote = rand() % 2;
    }

    ListNode* below = NULL;
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
            
            // is bigger or equal
            if (isBigger == 1 || isBigger == 0)
            {
                insertPosition = currentPosition;
                break;
            }
            currentPosition++;
            next = next->next;
        }

        SkipListNode node;
        // SkipListNode* node = (SkipListNode*)malloc(sizeof(SkipListNode));
        // node->value = (void*)malloc(list->dataSize);
        // node->below = below; // connect current node to the node in the layer below it

        node.value = (void*)malloc(list->dataSize);
        node.below = below;

        memcpy(node.value, value, list->dataSize);

        ListNode* insertNode = _ll_create_node(&node, sizeof(SkipListNode));

        _ll_insert_node(list->layers[i], insertNode, insertPosition);

        below = insertNode;
    }
    return EXIT_SUCCESS;
}

ListNode* _create_skip_list_node(const void* value, size_t dataSize) 
{
    SkipListNode* node = (SkipListNode*)malloc(sizeof(SkipListNode));
    if (node == NULL)
    {
        return NULL;
    }

    node->value = (void*)malloc(dataSize);
    node->below = NULL;
    if (node->value == NULL)
    {
        return NULL;
    }

    if (value != NULL) 
    {
        memcpy(node->value, value, dataSize);
    }

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

int sl_search(SkipList* list, void* value, int compare(const void*, const void*), 
            int bigger(const void*, const void*))
{
    int currentLayer = list->height - 1;
    LinkedList* layer = list->layers[currentLayer];
    ListNode* current = NULL;
    ListNode* next = layer->head;

    int isBigger = bigger(value, ((SkipListNode*)next->value)->value);
    while ((isBigger == -1 || isBigger == 0) && currentLayer > 0)
    {
        if (isBigger == 0) 
        {
            // found
            return EXIT_SUCCESS;
        }

        // assume that the head is bigger 
        // move down a layer 
        currentLayer--;
        layer= list->layers[currentLayer];
        next = layer->head;
        isBigger = bigger(value, ((SkipListNode*)next->value)->value);
    }

    if (isBigger == 0)
    {
        // found 
        return EXIT_SUCCESS;
    }

    if (isBigger == 1)
    {
        // move right and start at the head
        current = layer->head;
        next = next->next;
    }

    // begin search 
    while (currentLayer >= 0)
    {
        // assume null to be the biggest value
        if (next == NULL || bigger(((SkipListNode*)next->value)->value, value) == 1)
        {
            // move down a layer
            if (current == NULL)  // handle edge case
            {
                current = layer->head;
            }

            // move down
            current = ((SkipListNode*)current->value)->below;

            if (current == NULL)
            {
                // we have run out of levels to traverse to
                return EXIT_FAILURE;
            }
            
            next = current->next;
            currentLayer--;
            continue;
        }

        // value is assumed to be either matching or bigger
        if (compare(value, ((SkipListNode*)next->value)->value) == EXIT_SUCCESS)
        {
            // found
            return EXIT_SUCCESS;
        }        

        // value is bigger than current next
        // move forward
        current = next;
        next = next->next;
    }

    return EXIT_FAILURE;
}

int sl_search_int(SkipList* list, int value) 
{
    return sl_search(list, &value, compare_int, bigger_int);
}

int sl_free(SkipList* list, void free_item(void*))
{
    for (int i = 0; i < list->height; i++)
    {
        ll_free(list->layers[i], free_item);
    }

    free(list);
    list = NULL;
    return EXIT_SUCCESS;
}