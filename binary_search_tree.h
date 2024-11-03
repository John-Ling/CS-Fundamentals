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
static int insert_node(BSTNode** root, const int value);
int inorder_traversal(BSTNode* root);
int search(BSTNode* root, const int value);
int  free_tree(BSTNode* root);
static int delete_node(BSTNode** root, const int value);
static BSTNode* find_min_node(BSTNode* root); 