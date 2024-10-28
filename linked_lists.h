#define LINKED_LIST_LENGTH 10
#define START 0 // index of start of linked list
#define END  LINKED_LIST_LENGTH - 1 // index of end of linked list

typedef struct LinkedList_t
{
    int value;
    struct LinkedList_t* pointer;
} LinkedList;

LinkedList* generate(int values[], int nodeCount);
int display_linked_list(LinkedList** head);
int insert_node(LinkedList** head, int value, int position);
int delete_node(LinkedList** head, int position);
int free_linked_list(LinkedList** head);
int reverse(LinkedList** head);
