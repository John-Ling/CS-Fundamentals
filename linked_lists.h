const int LINKED_LIST_LENGTH = 10;
const int START = 0; // index of start of linked list
const int END = LINKED_LIST_LENGTH - 1; // index of end of linked list

typedef struct linked_list_t
{
    int value;
    struct linked_list_t* pointer;
} linked_list;

linked_list* generate(int values[], int nodeCount);
void display_linked_list(linked_list** head);
void insert_node(linked_list** head, int value, int position);
void delete_node(linked_list** head, int position);
void free_linked_list(linked_list** head);
void reverse(linked_list** head);
