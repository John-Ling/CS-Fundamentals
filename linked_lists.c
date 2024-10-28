#include <stdio.h>
#include <stdlib.h>

// implementation of a singly linked list for learning purposes

#include "linked_lists.h"

int main(void)
{
    int values[] = {56, 84, 23, 46, 91, 76, 21, 38, 11, 83};
	int nodeCount = sizeof(values) / sizeof(values[0]);

    // create linked list
    LinkedList* linkedList = generate(values, nodeCount); 

    // pointer to the first node (the head node) in a linked list
	LinkedList** head = &linkedList;
	printf("Displaying\n");
	display_linked_list(head);
	printf("Now reversing\n");
	reverse(head);
	display_linked_list(head);
	free_linked_list(head);
    return EXIT_SUCCESS;
}

int display_linked_list(LinkedList** head)
{
    LinkedList* temp = *head;
    while (temp != NULL)
    {
        printf("%i\n", temp->value);
        temp = temp->pointer;
    }
    return EXIT_SUCCESS;
}

int insert_node(LinkedList** head, int value, int position)
{
    LinkedList* temp = *head;
    LinkedList* node = malloc(sizeof(LinkedList));
    node->value = value;
    
    if (position == 0)
    {
        node->pointer = *head; // point node to the current head (pointer) of the list
        *head = node; // node is the new head of the linked list
    }
    else if (position == END)
    {
        while (temp->pointer != NULL) // traverse linked list until end
        {
            temp = temp->pointer;
        }
            
        temp->pointer = node; // point end of list to node
        node->pointer = NULL; // make node the new tail node by pointing it to null
    }
    else if (position > START && position < END)
    {
        // traverse linked list until position is reached
        for (int i = 0; i < position - 1; i++)
        {
            if (temp->pointer != NULL)
            {
                temp = temp->pointer;
            }
        }
        
        node->pointer = temp->pointer;
        temp->pointer = node;
    }

    return EXIT_SUCCESS;
}

int delete_node(LinkedList** head, int position)
{
    LinkedList* temp = *head;
    if (position == 0)
    {
        *head = (*head)->pointer; // change to the new head
        free(temp);
    }
    else if (position == END)
    {
        while (temp->pointer->pointer != NULL) // travel to penultimate node
        {
            temp = temp->pointer;
        }

        free(temp->pointer); // free pointer ahead of penultimate node
        temp->pointer = NULL; // set penultimate node to be the new tail node
    }
    else if (position > START && position < END)
    {
        for (int i = 0; i < position - 1; i++)
        {
            temp = temp->pointer;
        }
        
        LinkedList* nodeAhead = temp->pointer->pointer; // node after node to be freed
        free(temp->pointer);
        temp->pointer = nodeAhead;
    }
    else 
    {
        printf("Parameter 'position' should be between 0 and the length of the linked list\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int reverse(LinkedList** head)
{
	LinkedList* current = (*head)->pointer;
	LinkedList* previous = *head;
	previous->pointer = NULL;
	while (current != NULL)
	{
		LinkedList* next = current->pointer;
		current->pointer = previous;
		previous = current;
		current = next;
	}
	*head = previous;
    return EXIT_SUCCESS;
}

int free_linked_list(LinkedList** head)
{
    LinkedList* temp = *head;
    while (*head != NULL)
    {
        *head = (*head)->pointer;
        free(temp);
        temp = *head;
    }
    return EXIT_SUCCESS;
}

LinkedList* generate(int values[], int nodeCount) 
{
    LinkedList* head = malloc(sizeof(LinkedList));
	head->value = values[0];
	for (int i = 1; i < nodeCount; i++)
	{
		int value = values[i];
		insert_node(&head, value, i);
	}
    return head;
}