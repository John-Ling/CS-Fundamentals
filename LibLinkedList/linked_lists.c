#include "linked_lists.h"

// library that allows for a linked list of any type to be created for learning purposes

static int _ht_compare_int(const void* a, const void* b)
{
    return *(int*)a == *(int*)b ? EXIT_SUCCESS : EXIT_FAILURE;
}

static int _ht_compare_chr(const void* a, const void*b)
{
    return _ht_compare_int(a, b);
}

static int _ht_compare_str(const void* a, const void* b)
{
    char* s1 = (char*)a;
    char* s2 = (char*)b;

    while (1)
    {
        if (!*s1 && !*s2)
        {
            // both strings have finished at the same time
            break;
        }

        if ((!*s1 && *s2) || (*s1 && !*s2))
        {
            return EXIT_FAILURE;
        }

        if (*s1 != *s2)
        {
            return EXIT_FAILURE;
        }
        s1++;
        s2++;
    }

    // success
    return EXIT_SUCCESS;
}

static int _ht_free_void_array(void* arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
    return EXIT_SUCCESS;
}

// create an empty linked list by passing NULL
// or convert any array into a linked list by converting it into void pointers
// using array_to_void_array() and passing it
// byte size (aka datatype) of items being stored needs to be specified
LinkedList* ll_create(void* values[], const size_t n, const size_t typeSize)
{
    if (values == NULL && n != 0)
    {
        return NULL;
    }

    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        return NULL;
    }

    list->dataSize = typeSize;
    list->itemCount = 0;
    list->head = NULL;

    for (size_t i = 0; i < n; i++)
    {
        ll_insert(list, values[i], -1);
    }

    if (values != NULL)
    {
        _ht_free_void_array(values, n);
    }
    
    return list;
}

int ll_print(LinkedList* list, void print(const void*))
{
    ListNode* current = list->head;
    while (current != NULL)
    {
        print(current->value);
        current = current->next;
    }
    putchar('\n');
    return EXIT_SUCCESS;
}

// Creates a list node and returns its address
ListNode* _ll_create_node(const void* data, const size_t size)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL)
    {
        return NULL;
    }

    node->value = (void*)malloc(size);

    if ((*node).value == NULL)
    {
        free(node);
        return NULL;
    }

    memcpy(node->value, data, size);
    return node;
}

int _ll_insert_node(LinkedList* list, ListNode* node, const int index)
{
    node->next = NULL;
    // insert node into correct position
    if (list->head == NULL)
    {
        // list is empty
        list->head = node;
        return EXIT_SUCCESS;
    }

    // insert at head
    if (index == 0)
    {
        node->next = list->head;
        list->head = node;
    }
    else if (index == -1) // insert at tail
    {
        ListNode* current = list->head;

        // travel to end of list
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;    
    }
    else
    {
        ListNode* current = list->head;
        // travel to node that comes before index
        for (int i = 0; i < index - 1; i++)
        {
            if (current->next == NULL)
            {
                break;
            }
            current = current->next;
        }

        node->next = current->next;
        current->next = node;
    }

    return EXIT_SUCCESS;
}

// inserts a value at index in a linked list
// inserting at index -1 inserts at the end of the list
int ll_insert(LinkedList* list, const void* value, const int index)
{
    if (index > list->itemCount || index < -1 || list == NULL)
    {
        return EXIT_FAILURE;
    }
    
    list->itemCount++;

    ListNode* node = _ll_create_node(value, list->dataSize);
    return _ll_insert_node(list, node, index);
}

int ll_insert_int(LinkedList* list, int value, const int index)
{
    return ll_insert(list, &value, index);
}

int ll_insert_str(LinkedList* list, char* value, const int index)
{
    // since string can have variable length
    // we need to create a node of appropriate size
    // then insert

    char* s = value;
    int length = 0;
    while (*s)
    {
        s++;
        length++;
    }

    ListNode* node = _ll_create_node((void*)value, sizeof(char) * length);

    // use internal insert_node function to directly insert node
    return _ll_insert_node(list, node, index);
}

int ll_insert_flt(LinkedList* list, float value, const int index)
{
    return ll_insert(list, &value, index);
}

int ll_insert_dbl(LinkedList* list, double value, const int index)
{
    return ll_insert(list, &value, index);
}

int ll_insert_chr(LinkedList* list, char value, const int index)
{
    return ll_insert(list, &value, index);
}

int ll_delete(LinkedList* list, const int index, void free_item(void*))
{
    if (list->itemCount - 1 < 0 || index >= list->itemCount || index < -1)
    {
        return EXIT_FAILURE;
    }

    if (free_item == NULL)
    {
        free_item = free;
    }

    if (index == 0 || list->itemCount == 0)
    {
        ListNode* temp = list->head;
        list->head = list->head->next;
        free_item(temp->value);
        temp->value = NULL;
        free(temp);
        temp = NULL;
    }
    else if (index == -1)
    {
        ListNode* current = list->head;
        while (current->next->next != NULL) // travel to penultimate node
        {
            current = current->next;
        }
         // delete final node
        free_item(current->next->value);
        current->next->value = NULL;
        free(current->next);
        current->next = NULL;
    }
    else 
    {
        ListNode* current = list->head;
        
        // travel to node that comes before index
        for (int i = 0; i < index - 1; i++)
        {
            if (current->next == NULL)
            {
                break;
            }
            current = current->next;
        }

        // store node after index
        ListNode* temp = current->next;

        // isolate node to be freed by connect node at index with node after node to be freed
        current->next = current->next->next;

        free_item(temp->value);
        temp->value = NULL;
        free(temp);
        temp = NULL;
    }
    return EXIT_SUCCESS;
}

int ll_reverse(LinkedList* list)
{
    if (list->head == NULL)
    {
        // list is empty
        return EXIT_FAILURE;
    }
    ListNode* current = list->head->next;
    ListNode* previous = list->head;
    previous->next = NULL;
	while (current != NULL)
	{
		ListNode* next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	list->head = previous;
    return EXIT_SUCCESS;
}

int ll_search(LinkedList* list, void* search, int compare(const void*, const void*))
{
    ListNode* current = list->head;
    int position = 0;
    while (current != NULL)
    {
        if (compare(current->value, search) == EXIT_SUCCESS)
        {
            return position;
        }
        position++;
        current = current->next;
    }
    return -1;
}

int ll_search_int(LinkedList* list, int search)
{
    return ll_search(list, &search, _ht_compare_int);
}

int ll_search_str(LinkedList* list, char* search)
{
    return ll_search(list, (void*)search, _ht_compare_str);
}

int ll_search_chr(LinkedList* list, char search)
{
    return ll_search(list, &search, _ht_compare_chr);
}

// performs free_item() on each item in the linked list
// if free_item is NULL will default to basic free function
int ll_free(LinkedList* list, void (*free_item)(void*))
{
    // allow override of default free function with user's own
    // this allows for larger free functions for complex structs
    if (free_item == NULL)
    {
        free_item = free;
    }

    if (list == NULL)
    {
        free(list);
        list = NULL;
        return EXIT_SUCCESS;
    }

    if (list->head == NULL)
    {
        free(list);
        list = NULL;
        return EXIT_SUCCESS;
    }

    ListNode* previous = list->head;

    if (list->head->next != NULL)
    {
        list->head = list->head->next;
    }
    else 
    {
        free_item(previous->value);
        free(previous);
        free(list);
        previous = NULL;
        list = NULL;
        return EXIT_SUCCESS;
    }
    

    while (list->head != NULL)
    {
        free_item(previous->value);
        free(previous);
        previous = list->head;
        list->head = list->head->next;
    }

    free_item(previous->value);
    free(previous);
    free(list);
    previous = NULL;
    list = NULL;
    return EXIT_SUCCESS;
}

const struct LibLinkedList_l LibLinkedList = {
    .create = ll_create,
    .insert = ll_insert,
    .insert_int = ll_insert_int,
    .insert_chr = ll_insert_chr,
    .insert_dbl = ll_insert_dbl,
    .insert_flt = ll_insert_flt,
    .insert_str = ll_insert_str,
    .print = ll_print,
    .delete = ll_delete,
    .reverse = ll_reverse,
    .search = ll_search,
    .search_int = ll_search_int,
    .search_str = ll_search_str,
    .search_chr = ll_search_chr,
    .free = ll_free
};
