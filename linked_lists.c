#include <stdio.h>
#include <stdlib.h>

const int LINKED_LIST_LENGTH = 10;

struct linked_list_t
{
    int value;
    struct linked_list_t* pointer;
};
typedef struct linked_list_t linked_list;

linked_list generate(int values[]);

int main(void)
{
    int values[] = {56, 84, 23, 46, 91, 76, 21, 38, 11, 83};    
    linked_list myLinkedList = generate(values);
    return 0;
}

linked_list generate(int values[]) 
{
    // takes integer array values as an argument to generate a linked list
    linked_list myLinkedList;
    for (int i = 0; i < LINKED_LIST_LENGTH; i++)
    {
        linked_list node;
        node.value = values[i];
        linked_list* previousNode = &node;
        if (i > 0) // check if this is not the first node being generated
            previousNode->pointer = &node;
    }
}