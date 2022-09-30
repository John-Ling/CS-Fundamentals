#include <stdio.h>
#include <stdlib.h>

// implementation of a binary search tree for learning purposes

struct tree_t
{
    int value;
    struct tree_t* left;
    struct tree_t* right;
};
typedef struct tree_t tree;

tree* generate_tree();
void inorder_traversal(tree* root);
void search_tree(tree* root, int value);
void free_tree(tree* root);

int main(void)
{
    tree* root = generate_tree();

    search_tree(root, 39);
    free_tree(root);
    return 0;
}

void inorder_traversal(tree* root)
{
    if (root == NULL)
        return;
    inorder_traversal(root->left); // visit all nodes to the left
    printf("%i\n", root->value); // visit root node
    inorder_traversal(root->right); // visit all nodes to the right
}

void search_tree(tree* root, int value)
{
    // recursively search tree using binary search for value
    if (root == NULL)
    {
        printf("Could not find value\n");
        return;
    }

    if (value < root->value)
        search_tree(root->left, value);
    else if (value > root->value)  
        search_tree(root->right, value);
    else
    {
        printf("Found value\n");
        return;
    }
}

void free_tree(tree* root)
{
    // free allocated memory using postorder traversal left --> right --> root
    if (root == NULL)
        return;
    
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

tree* generate_tree()
{
    tree* root = malloc(sizeof(tree));
    root->value = 76;
    root->left = NULL;
    root->right = NULL;
    
    tree* node1 = malloc(sizeof(tree));
    node1->value = 50;
    node1->left = NULL;
    node1->right = NULL;

    root->left = node1;

    tree* node2 = malloc(sizeof(tree)); // allocate memory for another node
    node2->left = NULL;
    node2->right = NULL;
    node2->value = 90;

    root->right = node2;

    tree* node3 = malloc(sizeof(tree));
    node3->value = 39;
    node3->left = NULL;
    node3->right = NULL;

    node1->left = node3;

    tree* node4 = malloc(sizeof(tree));
    node4->value = 60;
    node4->left = NULL;
    node4->right = NULL;

    node1->right = node4;

    tree* node5 = malloc(sizeof(tree));
    node5->value = 87;
    node5->left = NULL;
    node5->right = NULL;

    node2->left = node5;

    tree* node6 = malloc(sizeof(tree));
    node6->value = 124;
    node6->left = NULL;
    node6->right = NULL;

    node2->right = node6;

    return root;
}