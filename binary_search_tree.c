#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_search_tree.h"

// implementation of a binary search tree for learning purposes

int main(void)
{
	int arr[5] = {5, 3, 1, 8, 9};
	BST* bst = create_tree(arr, 5);
	insert(bst, 900);
	insert(bst, 900);
	// puts("Inserting");
	// insert(root, 900);
	inorder_traversal(bst->root);
    // search_tree(root, 39);
	// delete(root, 39);
    // free_tree(root);
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

// interface to insert_node() where only the single
// pointer needs to be passed rather than a double pointer
int insert(BST* bst, const int value)
{
	// if bst is empty we can just create new node
	if (bst->itemCount != 0)
	{
		bst->itemCount++;
		return insert_node(&bst->root, value);
		
	}
	else
	{
		BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
		node->value = value;
		bst->root = node;
		bst->itemCount++;	
	}
	return EXIT_SUCCESS;
}

// insert a value into  binary search tree
static int insert_node(BSTNode** root, const int value)
{
	if ((*root) == NULL) // if binary search tree is empty or reached bottom (both will be null)
	{
		BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
		node->value = value;
		(*root) = node;
		return EXIT_SUCCESS;
	}

	if (value > (*root)->value)
	{
		return insert_node(&(*root)->right, value);
	}
	else if (value < (*root)->value)
	{
		return insert_node(&(*root)->left, value);
	}

	// duplicate values are not allowed
	return EXIT_FAILURE;
}

// interface to delete_node() similar to insert()
// int delete(BSTNode* root, const int value)
// {
// 	return EXIT_FAILURE;
// }

// static int delete_node(BSTNode** root, const int value)
// {
// 	if ((*root) == NULL)
// 	{
// 		return EXIT_SUCCESS;
// 	}

// 	if (value < (*root)->value)
// 	{
// 		return delete(&(*root)->left, value);
// 	}
// 	else if (value > (*root)->value)
// 	{
// 		return delete(&(*root)->right, value);
// 	}
// 	else
// 	{
// 		if (root->left == NULL && root->right && NULL)
// 		{
// 			free(root);
// 			root = NULL;
// 			printf("Deleted node\n");
// 			return root;
// 		}
// 		if (root->left == NULL)
// 		{
// 			BSTNode* tmp = root->right; // return the right child of the node to be deleted
// 			free(root); // delete the node to be deleted
// 			root = NULL;
// 			printf("Deleted node\n");
// 			return tmp;
// 		}
// 		if (root->right == NULL)
// 		{
// 			BSTNode* tmp = root->left; // return the left child of the node to be deleted
// 			free(root);
// 			root = NULL;
// 			printf("Deleted node\n");
// 			return tmp;
// 		}

// 		BSTNode* minNode = find_min_node(root->right); // find the inorder successor and copy it to the root node
// 		root->value = minNode->value;
// 		root->right = delete(root->right, minNode->value); // delete the node we copied from
// 	}
// 	return root;
// }

// helper function for delete()
// gets the smallest node in the left subtree of the right child of root
static BSTNode* find_min_node(BSTNode* root) 
{
	BSTNode* current = root;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

// free allocated memory using postorder traversal left --> right --> root
int free_tree(BSTNode* root)
{
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

// create empty binary search tree
// or tree with values arr pre-placed
BST* create_tree(int arr[], const int n)
{
	BST* bst = (BST*)malloc(sizeof(BST));
	bst->itemCount = 0;

    BSTNode* root = (BSTNode*)malloc(sizeof(BSTNode));
	bst->root = root;
    if (arr == NULL)
	{
		return bst;
	}

	for (int i = 0; i < n; i++)
	{
		insert(bst, arr[i]);
		bst->itemCount++;
	}
	return bst;
}