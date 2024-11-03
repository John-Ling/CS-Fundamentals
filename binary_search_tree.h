#define BAR_WIDTH 4

typedef struct BSTNode_t
{
    int value;
    struct BSTNode_t* left;
    struct BSTNode_t* right;
} BSTNode;

typedef struct BST_t
{
    int itemCount;
    BSTNode* root;
} BST;

BST* create_tree(int arr[], const int n);
int insert(BST* bst, const int value);
int print_tree(BST* bst);
static int insert_node(BSTNode** root, const int value);
static int tree_to_array(BSTNode* root, int arr[], int n, int index);
int search(BSTNode* root, const int value);
int free_tree(BSTNode* root);
int delete(BST* bst, const int value);
static int delete_node(BSTNode** root, const int value);
static BSTNode* find_min_node(BSTNode* root); 