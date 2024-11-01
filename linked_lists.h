#define LINKED_LIST_LENGTH 10
#define START 0 // index of start of linked list
#define END  LINKED_LIST_LENGTH - 1 // index of end of linked list

typedef struct ListNode_t
{
    int value;
    struct ListNode_t* next;
} ListNode;

typedef struct LinkedList_t
{
    int itemCount;
    ListNode* head; // front of list
} LinkedList;

LinkedList* create_list(int values[], int n);
int insert_node(LinkedList* list, const int value, const int position);
int print_list(LinkedList* list);
int delete_node(LinkedList* list, const int index);
int reverse_list(LinkedList* list);
int free_list(LinkedList* list);
