#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

// implementation of a basic binary tree for learning purposes

int main(void)
{
    node* root = generate_tree();
    
    inorder_traversal(root);

    free_tree(root);
    return 0;
}

void add_node_left(node* root, int value)
{
    node* node = malloc(sizeof(tree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    node* traversalPointer = root;
    while (traversalPointer->left != NULL)
        traversalPointer = traversalPointer->left;
    traversalPointer->left = node;
}

void add_node_right(node* root, int value)
{
    node* node = malloc(sizeof(tree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    node* traversalPointer = root;
    while (traversalPointer->right != NULL)
        traversalPointer = traversalPointer->right;
    traversalPointer->right = node;
}

void inorder_traversal(node* root)
{
    if (root == NULL)
        return;
    inorder_traversal(root->left);
    printf("%i\n", root->value);
    inorder_traversal(root->right);
}

void preorder_traversal(node* root)
{
    if (root == NULL)
        return;
    printf("%i\n", root->value);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(node* root)
{
    if (root == NULL)
        return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%i\n", root->value);
}

void free_tree(node* root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

node* generate_tree()
{
    node* root = malloc(sizeof(tree));
    root->value = 76;
    root->left = NULL;
    root->right = NULL;
    
    node* node1 = malloc(sizeof(tree));
    node1->value = 50;
    node1->left = NULL;
    node1->right = NULL;

    root->left = node1;

    node* node2 = malloc(sizeof(tree)); // allocate memory for another node
    node2->left = NULL;
    node2->right = NULL;
    node2->value = 90;

    root->right = node2;

    node* node3 = malloc(sizeof(tree));
    node3->value = 39;
    node3->left = NULL;
    node3->right = NULL;

    node1->left = node3;

    node* node4 = malloc(sizeof(tree));
    node4->value = 60;
    node4->left = NULL;
    node4->right = NULL;

    node1->right = node4;

    node* node5 = malloc(sizeof(tree));
    node5->value = 87;
    node5->left = NULL;
    node5->right = NULL;

    node2->left = node5;

    node* node6 = malloc(sizeof(tree));
    node6->value = 124;
    node6->left = NULL;
    node6->right = NULL;

    node2->right = node6;

    return root;
}