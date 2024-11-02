#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"

// implementation of a binary search tree for learning purposes

int main(void)
{
    
	BSTNode* root = create_tree(NULL, 0);
	puts("Chekcing");
	printf("%p\n", root);
	printf("%p\n", *root);
	if ((root) == NULL)
	{
		puts("Null");
		return EXIT_FAILURE;
	}
	insert_node(root, 900);
	// puts("Inserting");
	// insert(root, 900);
	inorder_traversal(root);
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

// interface to insert_node where only the single
// pointer needs to be passed rather than a double pointer
int insert(BSTNode* root, const int value)
{
	return insert_node(&root, value);
}

static int insert_node(BSTNode** root, const int value)
{
	if ((*root) == NULL) // if binary search tree is empty or reached bottom (both will be null)
	{
		BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
		node->value = value;
		(*root) = node;
		return EXIT_SUCCESS;
	}

	BSTNode** next;
	if (value > (*root)->value)
	{
		next = &(*root)->right;
	}
	else if (value < (*root)->value)
	{
		next = &(*root)->left;
	}
	else
	{
		return EXIT_SUCCESS;
	}
	return insert(next, value);
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

BSTNode* create_tree(int arr[], const int n)
{
    BSTNode* head = (BSTNode*)(malloc(sizeof(BSTNode)));
    head->value = 76;
	// root = &head;
	// printf("%p\n", *root);
    // return root;
	return head;
}