#include "linked_lists.h"

// library that allows for a linked list of any type to be created for learning purposes

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

// inserts a value at index in a linked list
// inserting at index -1 inserts at the end of the list
int ll_insert(LinkedList* list, void* value, const int index)
{
    if (index > list->itemCount || index < -1 || list == NULL)
    {
        return EXIT_FAILURE;
    }
    
    list->itemCount++;
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->value = (void**)malloc(sizeof(void*));
    if (node == NULL)
    {
        return EXIT_FAILURE;
    }

    memcpy(node->value, value, list->dataSize); // assign value 
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

int ll_insert_int(LinkedList* list, int value, const int index)
{
    return ll_insert(list, &value, index);
}

int ll_insert_str(LinkedList* list, char* value, const int index)
{
    return ll_insert(list, (void*)value, index);
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

int ll_delete(LinkedList* list, const int index)
{
    if (list->itemCount - 1 < 0 || index >= list->itemCount || index < -1)
    {
        return EXIT_FAILURE;
    }

    if (index == 0 || list->itemCount == 0)
    {
        ListNode* temp = list->head;
        list->head = list->head->next;
        free(temp->value);
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
        free(current->next->value);
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

        free(temp->value);
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

int ll_free(LinkedList* list)
{
    if (list->head == NULL)
    {
        free(list);
        list = NULL;
        return EXIT_FAILURE;
    }

    ListNode* previous = list->head;
    list->head = list->head->next;
    while (list->head != NULL)
    {
        free(previous->value);
        free(previous);
        previous = list->head;
        list->head = list->head->next;
    }
    free(previous->value);
    free(previous);
    free(list);
    previous = NULL;
    list = NULL;
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

    for (size_t i = 0; i < n; i++)
    {
        ll_insert(list, values[i], -1);
    }

    if (values != NULL)
    {
        free_void_array(values, n);
    }
    
    return list;
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
    .free = ll_free
};