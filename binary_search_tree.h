struct node_t
{
    int value;
    struct node_t* left;
    struct node_t* right;
};
typedef struct node_t node;

node* generate_tree();
void inorder_traversal(node* root);
void search_tree(node* root, int value);
void free_tree(node* root);
node* insert(node* root, int value);
node* delete(node* root, int value);
node* find_min_node(node* root);
