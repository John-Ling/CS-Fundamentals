#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// implementation of a linked list for learning purposes

#include "linked_lists.h"

int main(void)
{
    int values[] = {56, 84, 23, 46, 91, 76, 21, 38, 11, 83};
	int nodeCount = sizeof(values) / sizeof(values[0]);

    // create linked list
    linked_list* linkedList = generate(values, nodeCount); // pointer to the first node (the head node) in a linked list
	linked_list** head = &linkedList;
	printf("Displaying\n");
	display_linked_list(head);
	printf("Now reversing\n");
	reverse(head);
	display_linked_list(head);
	free_linked_list(head);
    return 0;
}

void display_linked_list(linked_list** head)
{
    linked_list* temp = *head;
    while (temp != NULL)
    {
        printf("%i\n", temp->value);
        temp = temp->pointer;
    }
}

void insert_node(linked_list** head, int value, int position)
{
    linked_list* temp = *head;
    linked_list* node = malloc(sizeof(linked_list));
    node->value = value;
    
    if (position == 0)
    {
        node->pointer = *head; // point node to the current head (pointer) of the list
        *head = node; // node is the new head of the linked list
    }
    else if (position == END)
    {
        while (temp->pointer != NULL) // traverse linked list until end
            temp = temp->pointer;

        temp->pointer = node; // point end of list to node
        node->pointer = NULL; // make node the new tail node by pointing it to null
    }
    else if (position > START && position < END)
    {
        // traverse linked list until position is reached
        for (int i = 0; i < position - 1; i++)
        {
            if (temp->pointer != NULL)
                temp = temp->pointer;
        }
        
        node->pointer = temp->pointer;
        temp->pointer = node;
    }
}

void delete_node(linked_list** head, int position)
{
    linked_list* temp = *head;
    if (position == 0)
    {
        *head = (*head)->pointer; // change to the new head
        free(temp);
    }
    else if (position == END)
    {
        while (temp->pointer->pointer != NULL) // travel to penultimate node
            temp = temp->pointer;

        free(temp->pointer); // free pointer ahead of penultimate node
        temp->pointer = NULL; // set penultimate node to be the new tail node
    }
    else if (position > START && position < END)
    {
        for (int i = 0; i < position - 1; i++)
            temp = temp->pointer;
        linked_list* nodeAhead = temp->pointer->pointer; // node after node to be freed
        free(temp->pointer);
        temp->pointer = nodeAhead;
    }
    else 
        printf("Parameter 'position' should be between 0 and the length of the linked list\n");
}

void reverse(linked_list** head)
{
	linked_list* current = (*head)->pointer;
	linked_list* previous = *head;
	previous->pointer = NULL;
	while (current != NULL)
	{
		linked_list* next = current->pointer;
		current->pointer = previous;
		previous = current;
		current = next;
	}
	*head = previous;
}

void free_linked_list(linked_list** head)
{
    linked_list* temp = *head;
    while (*head != NULL)
    {
        *head = (*head)->pointer;
        free(temp);
        temp = *head;
    }
}

linked_list* generate(int values[], int nodeCount) 
{
    linked_list* head = malloc(sizeof(linked_list));
	head->value = values[0];
	for (int i = 1; i < nodeCount; i++)
	{
		int value = values[i];
		insert_node(&head, value, i);
	}
    return head;
}