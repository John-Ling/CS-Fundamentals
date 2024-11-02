typedef struct BSTNode_t
{
    int value;
    struct BSTNode_t* left;
    struct BSTNode_t* right;
} BSTNode;

BSTNode* create_tree(int arr[], const int n);
int insert(BSTNode* root, const int value);
static int insert_node(BSTNode** root, const int value);
int inorder_traversal(BSTNode* root);
int search(BSTNode* root, const int value);
int  free_tree(BSTNode* root);
BSTNode* delete(BSTNode* root, const int value);
BSTNode* find_min_node(BSTNode* root);