#include "linked_lists.h"

// library that allows for a linked list of any type to be created for learning purposes

// TODO
// make linked list generic see https://www.geeksforgeeks.org/generic-linked-list-in-c-2/

int ll_print(LinkedList* list, void print(void*))
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
    if (index > list->itemCount || index < -1)
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

    puts("Setting value");
    memcpy(node->value, value, list->dataSize); // assign value 

    puts("Setting");
    if (list->head == NULL)
    {
        // list is empty
        list->head = node;
        return EXIT_SUCCESS;
    }

    puts("inserting elsewhere");
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

int ll_delete(LinkedList* list, const int index)
{
    if (list->itemCount - 1 < 0 || index >= list->itemCount || index < -1)
    {
        return EXIT_FAILURE;
    }

    list->itemCount--;

    // if only 1 item in linked list
    if (list->itemCount == 0)
    {
        free(list->head->value);
        free(list->head);
        list->head->value = NULL;
        list->head = NULL;
        return EXIT_SUCCESS;
    }

    if (index == 0)
    {
        ListNode* temp = list->head;
        list->head = list->head->next;
        free(temp->value);
        free(temp);
        temp->value = NULL;
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
        free(current->next);
        current->next->value = NULL;
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
        free(temp);
        temp->value = NULL;
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
// using CONVERT_ARRAY/convert array and 
LinkedList* ll_create(void* values[], const size_t n)
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

    size_t typeSize = sizeof(typeof(*values));
    list->dataSize = typeSize;
    list->itemCount = 0;


    for (int i = 0; i < n; i++)
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
    .print = ll_print,
    .delete = ll_delete,
    .reverse = ll_reverse,
    .free = ll_free
};