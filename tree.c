#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

// implementation of a basic binary tree for learning purposes

int main(void)
{
    Node* root = generate_tree();
    inorder_traversal(root);

    free_tree(root);
    return EXIT_SUCCESS;
}

int add_node_left(Node* root, const int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    Node* traversalPointer = root;
    while (traversalPointer->left != NULL)
    {
        traversalPointer = traversalPointer->left;
    }
    traversalPointer->left = node;
    return EXIT_SUCCESS;
}

int add_node_right(Node* root, const int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    Node* traversalPointer = root;
    while (traversalPointer->right != NULL)
    {
        traversalPointer = traversalPointer->right;
    }
    traversalPointer->right = node;
    return EXIT_SUCCESS;
}

int inorder_traversal(Node* root)
{
    if (root == NULL)
    {
        return EXIT_FAILURE;
    }
        
    inorder_traversal(root->left);
    printf("%i\n", root->value);
    inorder_traversal(root->right);
    return EXIT_SUCCESS;
}

int preorder_traversal(Node* root)
{
    if (root == NULL)
    {
        return EXIT_FAILURE;
    }
    printf("%i\n", root->value);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
    return EXIT_SUCCESS;
}

int postorder_traversal(Node* root)
{
    if (root == NULL)
    {
        return EXIT_FAILURE;
    }
        
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%i\n", root->value);
    return EXIT_SUCCESS;
}

int free_tree(Node* root)
{
    if (root == NULL)
    {
        return EXIT_FAILURE;
    }
        
    free_tree(root->left);
    free_tree(root->right);
    free(root);
    return EXIT_SUCCESS;
}

Node* generate_tree()
{
    Node* root = (Node*)malloc(sizeof(Node));
    root->value = 76;
    root->left = NULL;
    root->right = NULL;
    
    Node* node1 = (Node*)malloc(sizeof(Node));
    node1->value = 50;
    node1->left = NULL;
    node1->right = NULL;

    root->left = node1;

    Node* node2 = (Node*)malloc(sizeof(Node)); // allocate memory for another node
    node2->left = NULL;
    node2->right = NULL;
    node2->value = 90;

    root->right = node2;

    Node* node3 = (Node*)malloc(sizeof(Node));
    node3->value = 39;
    node3->left = NULL;
    node3->right = NULL;

    node1->left = node3;

    Node* node4 = (Node*)malloc(sizeof(Node));
    node4->value = 60;
    node4->left = NULL;
    node4->right = NULL;

    node1->right = node4;

    Node* node5 = (Node*)malloc(sizeof(Node));
    node5->value = 87;
    node5->left = NULL;
    node5->right = NULL;

    node2->left = node5;

    Node* node6 = (Node*)malloc(sizeof(Node));
    node6->value = 124;
    node6->left = NULL;
    node6->right = NULL;

    node2->right = node6;

    return root;
}