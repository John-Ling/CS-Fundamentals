#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_search_tree.h"

// implementation of a binary search tree for learning purposes

int main(void)
{
	BST* bst = create_tree(NULL, 0);
	insert(bst, 50);
	insert(bst, 30);
	insert(bst, 70);
	insert(bst, 20);
	insert(bst, 40);
	insert(bst, 60);
	insert(bst, 80);
	// puts("Inserting");
	// insert(root, 900);
	print_tree(bst);
    // search_tree(root, 39);
	// delete(root, 39);
    // free_tree(root);
    return EXIT_SUCCESS;
}

// nicely prints out content of tree
int print_tree(BST* bst)
{
	if (bst->itemCount == 0)
	{
		puts("Tree is empty");
		return EXIT_FAILURE;
	}

	// array representation of tree
	int tree[bst->itemCount];

	// perform preorder traversal of tree and populate array
	tree_to_array(bst->root, tree, bst->itemCount, 0);
	for (int i = 0; i < bst->itemCount; i++)
	{
		printf("%d ", tree[i]);
	}
	putchar('\n');

	// print items in tree array

	int index = 0;
	while (2*index+2 < bst->itemCount)
	{
		printf("%d\n", tree[index]);
		printf("%d\n", tree[2*index + 1]);
		printf("%d\n", tree[2*index + 2]);
		index++;
	}

	return EXIT_SUCCESS;
}

// traverses subtree starting at root using inorder traversal
// returns integer represnting line width for use in formatting by search_tree()
static int tree_to_array(BSTNode* root, int arr[], int n, int index)
{
    if (root == NULL)
	{
		return EXIT_SUCCESS;
	}

	arr[index] = root->value;
	if (2*index + 1 < n)
	{
		tree_to_array(root->left, arr, n, 2*index + 1);	
	}
	if (2*index + 2 < n)
	{
		tree_to_array(root->right, arr, n, 2*index + 2);
	}

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
	if ((*root) == NULL) 
	{
		// reached base of tree
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
int delete(BST* bst, const int value)
{
	if (bst->itemCount == 0)
	{
		// tree is empty
		return EXIT_FAILURE;
	}

	return delete_node(&bst->root, value);
}

static int delete_node(BSTNode** root, const int value)
{
	if ((*root) == NULL)
	{
		// reached base of tree
		return EXIT_SUCCESS;
	}

	if (value < (*root)->value)
	{
		return delete_node(&(*root)->left, value);
	}
	else if (value > (*root)->value)
	{
		return delete_node(&(*root)->right, value);
	}

	// reached value to delete
	if ((*root)->left == NULL && (*root)->right && NULL)
	{
		// node has no children
		free(*root);
		*root = NULL;
		return EXIT_SUCCESS;
	}
	else if ((*root)->left == NULL)
	{
		// node to be deleted has right child
		BSTNode* rightChild = (*root)->right;
		free(*root); // delete the node to be deleted
		*root = rightChild;
		return EXIT_SUCCESS;
	}
	else if ((*root)->right == NULL)
	{
		// node to be deleted has left child

		BSTNode* leftChild = (*root)->left;
		free(*root);
		*root = leftChild;
		return EXIT_SUCCESS;
	}

	// node has 2 children
	// therefore we replace node with its inorder successor
	// find the inorder successor of the right child node
	// then delete node we copied from

	// find the inorder successor and copy it to the root node
	BSTNode* inorderSuccessor = find_min_node((*root)->right); 
	(*root)->value = inorderSuccessor->value;

	// delete inorder successor
	return delete_node(&(*root)->right, inorderSuccessor->value);
}

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