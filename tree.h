struct node_t
{
    int value;
    struct node_t* left;
    struct node_t* right;
};
typedef struct node_t node;

node* generate_tree();
void inorder_traversal(node* root);
void preorder_traversal(node* root);
void postorder_traversal(node* root);
void free_tree(node* root);
void add_node_left(node* root, int value);
void add_node_right(node* root, int value);
