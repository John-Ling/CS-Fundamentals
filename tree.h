typedef struct Node_t
{
    int value;
    struct Node_t* left;
    struct Node_t* right;
} Node;

Node* generate_tree();
int inorder_traversal(Node* root);
int preorder_traversal(Node* root);
int postorder_traversal(Node* root);
int free_tree(Node* root);
int add_node_left(Node* root, const int value);
int add_node_right(Node* root, const int value);
