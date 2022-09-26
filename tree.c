#include <stdio.h>
#include <stdlib.h>

// implementation of a basic binary tree for learning purposes
struct tree_t
{
    int value;
    struct tree_t* left;
    struct tree_t* right;
};
typedef struct tree_t tree;

tree* generate_tree();
void inorder_traversal(tree* root);
void preorder_traversal(tree* root);
void postorder_traversal(tree* root);
void free_tree(tree* root);
void add_node_left(tree* root, int value);
void add_node_right(tree* root, int value);

int main(void)
{
    tree* root = generate_tree();
    add_node_left(root, 40);
    add_node_right(root, 30);
    add_node_left(root, 10);
    //inorder_traversal(root);
    // preorder_traversal(root);
    //postorder_traversal(root);
    inorder_traversal(root);

    free_tree(root);
    return 0;
}

void add_node_left(tree* root, int value)
{
    tree* node = malloc(sizeof(tree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    tree* traversalPointer = root;
    while (traversalPointer->left != NULL)
        traversalPointer = traversalPointer->left;
    traversalPointer->left = node;
}

void add_node_right(tree* root, int value)
{
    tree* node = malloc(sizeof(tree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    tree* traversalPointer = root;
    while (traversalPointer->right != NULL)
        traversalPointer = traversalPointer->right;
    traversalPointer->right = node;
}

void inorder_traversal(tree* root)
{
    if (root == NULL)
        return;
    inorder_traversal(root->left);
    printf("%i\n", root->value);
    inorder_traversal(root->right);
}

void preorder_traversal(tree* root)
{
    if (root == NULL)
        return;
    printf("%i\n", root->value);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(tree* root)
{
    if (root == NULL)
        return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%i\n", root->value);
}

void free_tree(tree* root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

tree* generate_tree()
{
    tree* root = malloc(sizeof(tree));
    root->value = 2;
    root->left = NULL;
    root->right = NULL;
    
    tree* node1 = malloc(sizeof(tree));
    node1->value = 1;

    root->left = node1;

    tree* node2 = malloc(sizeof(tree)); // allocate memory for another node
    node2->value = 3;

    root->right = node2;

    tree* node3 = malloc(sizeof(tree));
    node3->value = 4;
    node3->left = NULL;
    node3->right = NULL;

    node1->left = node3;

    tree* node4 = malloc(sizeof(tree));
    node4->value = 5;
    node4->left = NULL;
    node4->right = NULL;

    node1->right = node4;

    tree* node5 = malloc(sizeof(tree));
    node5->value = 6;
    node5->left = NULL;
    node5->right = NULL;

    node2->right = node5;

    tree* node6 = malloc(sizeof(tree));
    node6->value = 7;
    node6->left = NULL;
    node6->right = NULL;

    node2->left = node6;

    return root;
}