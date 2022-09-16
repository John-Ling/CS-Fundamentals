#include <stdio.h>
#include <stdlib.h>

const int LINKED_LIST_LENGTH = 10;

struct linked_list_t
{
    int value;
    struct linked_list_t* pointer;
};
typedef struct linked_list_t linked_list;

linked_list* generate(int values[]);
void display_linked_list(linked_list** head);
void insert_node(linked_list** head, int value, int position);
void free_linked_list(linked_list** head);

int main(void)
{    
    const int START = 0;
    const int END = 10;
    int values[] = {56, 84, 23, 46, 91, 76, 21, 38, 11, 83};
    const int POSITION = 4;

    // create linked list
    linked_list* linkedList = generate(values); // pointer to the first node (the head node) in a linked list
    linked_list** head = &linkedList; // pointer to the first pointer 
    // struct** is a "double pointer" it stores the address of a another pointer that in itself stores address (pointer-ception?)
    // because all the nodes in a linked list are pointers themselves to access nodes in a linked lists without permanently changing them
    // you use a double pointer much like how you would use a regular pointer when dealing with non-pointer values

    //example use of a linked list
    insert_node(head, 256, END);

    display_linked_list(head);
    free_linked_list(head);
    return 0;
}

void display_linked_list(linked_list** head)
{
    linked_list* temp = malloc(sizeof(linked_list));
    temp = *head;
    while (temp != NULL)
    {
        printf("%i\n", temp->value);
        temp = temp->pointer;
    }
    free(temp);
}

void insert_node(linked_list** head, int value, int position)
{
    linked_list* node = malloc(sizeof(linked_list));
    node->value = value;
    
    if (position == 0)
    {
        node->pointer = *head; // point node to the current head (pointer) of the list
        *head = node; // node is the new head of the linked list
    }
    else if (position  == LINKED_LIST_LENGTH)
    {
        linked_list* temp = malloc(sizeof(linked_list));
        temp = *head; // temp points to head so it can access head's nodes

        while (temp->pointer != NULL) // traverse linked list until end
            temp = temp->pointer;

        temp->pointer = node; // point end of list to node
        node->pointer = NULL; // make node the new tail node by pointing it to null
    }
    else
    {
        linked_list* temp = malloc(sizeof(linked_list));
        temp = *head;

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

void free_linked_list(linked_list** head)
{
    linked_list* previousNode = malloc(sizeof(linked_list));
    previousNode = *head;
    while (*head != NULL)
    {
        *head = (*head)->pointer;
        free(previousNode);
        previousNode = *head;
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