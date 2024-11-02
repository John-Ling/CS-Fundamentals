typedef struct BSTNode_t
{
    int value;
    struct BSTNode_t* left;
    struct BSTNode_t* right;
} BSTNode;

BSTNode* generate_tree();
int inorder_traversal(BSTNode* root);
int search_tree(BSTNode* root, const int value);
int  free_tree(BSTNode* root);
BSTNode* insert_tree_node(BSTNode* root, const int value);
BSTNode* delete(BSTNode* root, const int value);
BSTNode* find_min_node(BSTNode* root);
