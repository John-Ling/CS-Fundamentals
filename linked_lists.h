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

struct LibLinkedList_l {
    LinkedList* (*create_list)(int[], int);
    int (*insert_node)(LinkedList*, const int, const int);
    int (*print_list)(LinkedList*);
    int (*delete_node)(LinkedList*, const int);
    int (*reverse_list)(LinkedList*);
    int (*free_list)(LinkedList*);
};

extern const struct LibLinkedList_l LibLinkedList;