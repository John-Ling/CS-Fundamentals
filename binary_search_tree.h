typedef struct Node_T
{
    int value;
    struct Node_T* left;
    struct Node_T* right;
} Node;

Node* generate_tree();
int inorder_traversal(Node* root);
int search_tree(Node* root, int value);
int  free_tree(Node* root);
Node* insert(Node* root, int value);
Node* delete(Node* root, int value);
Node* find_min_node(Node* root);
