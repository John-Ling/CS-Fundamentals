#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// implementation of a singly linked list for learning purposes

#include "linked_lists.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Pass values to form the array\n");
        return EXIT_FAILURE;
    }
    const int n = argc - 1;

    int arr[n];
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }

    LinkedList* list = create_list(arr, n);

    // basic uses of a linked list
    insert_node(list, 50, -1);
    insert_node(list, 10, 0);
    insert_node(list, 43, 4);

    delete_node(list, -1);

    print_list(list);
    reverse_list(list);
    print_list(list);

    free_list(list);

    return EXIT_SUCCESS;
}

int print_list(LinkedList* list)
{
    ListNode* current = list->head;
    while (current != NULL)
    {
        printf("%i ", current->value);
        current = current->next;
    }
    puts("");
    return EXIT_SUCCESS;
}

// inserts a value at index in a linked list
int insert_node(LinkedList* list, const int value, const int index)
{
    if (index > list->itemCount || index < -1)
    {
        return EXIT_FAILURE;
    }
    
    list->itemCount++;
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL)
    {
        return EXIT_FAILURE;
    }

    node->value = value;

    if (list->head == NULL)
    {
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

int delete_node(LinkedList* list, const int index)
{

    if (list->itemCount - 1 < 0 || index >= list->itemCount || index < -1)
    {
        return EXIT_FAILURE;
    }

    list->itemCount--;

    if (index == 0)
    {
        ListNode* temp = list->head;
        list->head = list->head->next;
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
        free(current->next); // delete final node
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

        free(temp);
        temp = NULL;
    }
    return EXIT_SUCCESS;
}

int reverse_list(LinkedList* list)
{
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

int free_list(LinkedList* list)
{
    ListNode* previous = list->head;
    list->head = list->head->next;
    while (list->head != NULL)
    {
        free(previous);
        previous = list->head;
        list->head = list->head->next;
    }
    free(previous);
    previous = NULL;
    free(list);
    return EXIT_SUCCESS;
}

LinkedList* create_list(int values[], int n) 
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        puts("Failed to create list");
        exit(1);
    }
    list->itemCount = 0;
    for (int i = 0; i < n; i++)
    {
        insert_node(list, values[i], -1);
    }
    return list;
}

// test basic features of linked list
static int run_test(void)
{
    int values[] = {56, 84, 23, 46, 91, 76, 21, 38, 11, 83};
	int nodeCount = sizeof(values) / sizeof(values[0]);
    // create linked list
    LinkedList* list = create_list(values, nodeCount); 

    // test insertion
    assert(insert_node(list, 300, 2) == EXIT_SUCCESS);
    assert(insert_node(list, 600, 0) == EXIT_SUCCESS);
    assert(insert_node(list, 900, -1) == EXIT_SUCCESS);

    // test invalid insertion
    assert(insert_node(list, 900, 999) == EXIT_FAILURE);
    assert(insert_node(list, 900, -2) == EXIT_FAILURE);

    // test deletion
    assert(delete_node(list, 0) == EXIT_SUCCESS);
    assert(delete_node(list, 2) == EXIT_SUCCESS);
    assert(delete_node(list, -1) == EXIT_SUCCESS);

    // test invalid deletion
    assert(delete_node(list, 9999) == EXIT_FAILURE);
    assert(delete_node(list, -2) == EXIT_FAILURE);

    // check if print and reverse works
    print_list(list);
    reverse_list(list);
    print_list(list);

    free_list(list);
    return EXIT_SUCCESS;
}