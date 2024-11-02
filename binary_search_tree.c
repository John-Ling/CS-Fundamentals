#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"

// implementation of a binary search tree for learning purposes

int main(void)
{
    BSTNode* root = generate_tree();
	inorder_traversal(root);
    search_tree(root, 39);
	delete(root, 39);
    free_tree(root);
    return EXIT_SUCCESS;
}

int inorder_traversal(BSTNode* root)
{
    if (root == NULL)
	{
		return EXIT_FAILURE;
	}
    inorder_traversal(root->left); // visit all nodes to the left
    printf("%i\n", root->value); // visit root node
    inorder_traversal(root->right); // visit all nodes to the right
	return EXIT_SUCCESS;
}

int search_tree(BSTNode* root, const int value)
{
    // recursively search tree using binary search for value
    if (root == NULL)
    {
        printf("Could not find value\n");
        return EXIT_FAILURE;
    }

    if (value < root->value)
	{
		return search_tree(root->left, value);
	}
    else if (value > root->value)  
	{
		return search_tree(root->right, value);
	}
    else
    {
        printf("Found value\n");
        return EXIT_SUCCESS;
    }
}

BSTNode* insert_tree_node(BSTNode* root, const int value)
{
	if (root == NULL) // if binary search tree is empty or reached bottom (both will be null)
	{
		BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
		node->value = value;
		node->left = NULL;
		node->right = NULL;	
		return node;
	}

	if (value > root->value)
	{
		root->right = insert_tree_node(root->right, value);
	}
	else if (value < root->value)
	{
		root->left = insert_tree_node(root->left, value); 
	}
	return root;
}

BSTNode* delete(BSTNode* root, const int value)
{
	if (root == NULL)
	{
		return root;
	}

	if (value < root->value)
	{
		root->left = delete(root->left, value);
	}
	else if (value > root->value)
	{
		root->right = delete(root->right, value);
	}
	else
	{
		if (root->left == NULL && root->right && NULL)
		{
			free(root);
			root = NULL;
			printf("Deleted node\n");
			return root;
		}
		if (root->left == NULL)
		{
			BSTNode* tmp = root->right; // return the right child of the node to be deleted
			free(root); // delete the node to be deleted
			root = NULL;
			printf("Deleted node\n");
			return tmp;
		}
		if (root->right == NULL)
		{
			BSTNode* tmp = root->left; // return the left child of the node to be deleted
			free(root);
			root = NULL;
			printf("Deleted node\n");
			return tmp;
		}

		BSTNode* minNode = find_min_node(root->right); // find the inorder successor and copy it to the root node
		root->value = minNode->value;
		root->right = delete(root->right, minNode->value); // delete the node we copied from
	}
	return root;
}

BSTNode* find_min_node(BSTNode* root) // get the smallest node in the left subtree of the right child of root
{
	BSTNode* current = root;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

int free_tree(BSTNode* root)
{
    // free allocated memory using postorder traversal left --> right --> root
    if (root == NULL)
    {
	    return EXIT_SUCCESS;
    }
    
    free_tree(root->left);
    free_tree(root->right);
    free(root);
    root = NULL;
    return EXIT_SUCCESS;
}

BSTNode* generate_tree()
{
    BSTNode* root = (BSTNode*)(malloc(sizeof(BSTNode)));
    root->value = 76;
    root->left = NULL;
    root->right = NULL;
	root = insert_tree_node(root, 50);
	root = insert_tree_node(root, 90);
	root = insert_tree_node(root, 39);
	root = insert_tree_node(root, 60);
	root = insert_tree_node(root, 87);
	root = insert_tree_node(root, 124);
    return root;
}