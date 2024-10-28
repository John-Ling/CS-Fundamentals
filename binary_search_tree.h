typedef struct Node_T
{
    int value;
    struct Node_T* left;
    struct Node_T* right;
} Node;

Node* generate_tree();
int inorder_traversal(Node* root);
int search(Node* root, const int value);
int  free_tree(Node* root);
Node* insert(Node* root, const int value);
Node* delete(Node* root, const int value);
Node* find_min_node(Node* root);
