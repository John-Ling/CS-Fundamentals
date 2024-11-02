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
int insert(LinkedList* list, const int value, const int position);
int print_list(LinkedList* list);
int delete(LinkedList* list, const int index);
int reverse(LinkedList* list);
int free_list(LinkedList* list);

struct LibLinkedList_l {
    LinkedList* (*create_list)(int[], int);
    int (*insert)(LinkedList*, const int, const int);
    int (*print_list)(LinkedList*);
    int (*delete)(LinkedList*, const int);
    int (*reverse)(LinkedList*);
    int (*free_list)(LinkedList*);
};

extern const struct LibLinkedList_l LibLinkedList;