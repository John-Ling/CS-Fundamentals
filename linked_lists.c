#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int LINKED_LIST_LENGTH = 10;
const int START = 0; // index of start of linked list
const int END = LINKED_LIST_LENGTH - 1; // index of end of linked list

struct linked_list_t
{
    int value;
    struct linked_list_t* pointer;
};
typedef struct linked_list_t linked_list;

linked_list* generate(int values[]);
void display_linked_list(linked_list* head, linked_list* pointer);
void insert_node(linked_list* head, linked_list* traversalPointer, int value, int position);
void delete_node(linked_list* head, linked_list* traversalPointer, int position);
void free_linked_list(linked_list* head, linked_list* traversalPointer);

int main(void)
{    
    const int START = 0;
    const int END = LINKED_LIST_LENGTH - 1;
    int values[] = {56, 84, 23, 46, 91, 76, 21, 38, 11, 83};
    const int POSITION = 4;

    // create linked list
    linked_list* head = generate(values); // pointer to the first node (the head node) in a linked list
    linked_list* traversalPointer = malloc(sizeof(linked_list)); // pointer to traverse linked list

    //example use of a linked list
    delete_node(head, traversalPointer, END);
    display_linked_list(head, traversalPointer);
    free_linked_list(head, traversalPointer);
    free(traversalPointer);
    return 0;
}

void display_linked_list(linked_list* head, linked_list* traversalPointer)
{
    traversalPointer = head;
    while (traversalPointer != NULL)
    {
        printf("%i\n", traversalPointer->value);
        traversalPointer = traversalPointer->pointer;
    }
}

void insert_node(linked_list* head, linked_list* traversalPointer, int value, int position)
{
    linked_list* node = malloc(sizeof(linked_list));
    node->value = value;
    
    if (position == 0)
    {
        node->pointer = head; // point node to the current head (pointer) of the list
        head = node; // node is the new head of the linked list
    }
    else if (position == END)
    {
        traversalPointer = head;
        while (traversalPointer->pointer != NULL) // traverse linked list until end
            traversalPointer = traversalPointer->pointer;

        traversalPointer->pointer = node; // point end of list to node
        node->pointer = NULL; // make node the new tail node by pointing it to null
    }
    else if (position > START && position < END)
    {
        traversalPointer = head;

        // traverse linked list until position is reached
        for (int i = 0; i < position - 1; i++)
        {
            if (traversalPointer->pointer != NULL)
                traversalPointer = traversalPointer->pointer;
        }
        
        node->pointer = traversalPointer->pointer;
        traversalPointer->pointer = node;
    }
}

void delete_node(linked_list* head, linked_list* traversalPointer, int position)
{
    traversalPointer = head; // store the current head pointer
    if (position == 0)
    {
        head = (head)->pointer; // change to the new head
        free(traversalPointer); // free the head pointer stored in traversalPointer
    }
    else if (position == END)
    {
        while (traversalPointer->pointer->pointer != NULL) // travel to penultimate node
            traversalPointer = traversalPointer->pointer;

        free(traversalPointer->pointer); // free pointer ahead of penultimate node
        traversalPointer->pointer = NULL; // set penultimate node to be the new tail node
    }
    else if (position > START && position < END)
    {
        for (int i = 0; i < position - 1; i++)
        {
            traversalPointer = traversalPointer->pointer;
        }
        traversalPointer->pointer = traversalPointer->pointer;
    }
    else 
        printf("Parameter 'position' should be between 0 and the length of the linked list\n");
}

void free_linked_list(linked_list* head, linked_list* traversalPointer)
{
    traversalPointer = head;
    while (head != NULL)
    {
        head = (head)->pointer;
        free(traversalPointer);
        traversalPointer = head;
    }
}

linked_list* generate(int values[]) 
{
    linked_list* headNode = malloc(sizeof(linked_list));
    linked_list* node1 = malloc(sizeof(linked_list));
    linked_list* node2 = malloc(sizeof(linked_list));
    linked_list* node3 = malloc(sizeof(linked_list));
    linked_list* node4 = malloc(sizeof(linked_list));
    linked_list* node5 = malloc(sizeof(linked_list));
    linked_list* node6 = malloc(sizeof(linked_list));
    linked_list* node7 = malloc(sizeof(linked_list));
    linked_list* node8 = malloc(sizeof(linked_list));
    linked_list* tailNode = malloc(sizeof(linked_list));

    headNode->value = values[0];
    node1->value = values[1];
    node2->value = values[2];
    node3->value = values[3];
    node4->value = values[4];
    node5->value = values[5];
    node6->value = values[6];
    node7->value = values[7];
    node8->value = values[8];
    tailNode->value = values[9];

    headNode->pointer = node1;
    node1->pointer = node2;
    node2->pointer = node3;
    node3->pointer = node4;
    node4->pointer = node5;
    node5->pointer = node6;
    node6->pointer = node7;
    node7->pointer = node8;
    node8->pointer = tailNode;
    tailNode->pointer = NULL;

    return headNode;
}