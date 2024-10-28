#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"

// implementation of a binary search tree for learning purposes

int main(void)
{
    Node* root = generate_tree();
	inorder_traversal(root);
    search_tree(root, 39);
    free_tree(root);
    return EXIT_SUCCESS;
}

int inorder_traversal(Node* root)
{
    if (root == NULL)
	{
		return EXIT_SUCCESS;
	}
    inorder_traversal(root->left); // visit all nodes to the left
    printf("%i\n", root->value); // visit root node
    inorder_traversal(root->right); // visit all nodes to the right
	return EXIT_SUCCESS;
}

int search_tree(Node* root, int value)
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

Node* insert(Node* root, int value)
{
	if (root == NULL) // if binary search tree is empty or reached bottom (both will be null)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->value = value;
		node->left = NULL;
		node->right = NULL;	
		return node;
	}

	if (value > root->value)
	{
		root->right = insert(root->right, value);
	}
	else if (value < root->value)
	{
		root->left = insert(root->left, value); 
	}
	return root;
}

Node* delete(Node* root, int value)
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
			return root;
		}
		if (root->left == NULL)
		{
			Node* tmp = root->right; // return the right child of the node to be deleted
			free(root); // delete the node to be deleted
			return tmp;
		}
		if (root->right == NULL)
		{
			Node* tmp = root->left; // return the left child of the node to be deleted
			free(root);
			return tmp;
		}

		Node* minNode = find_min_node(root->right); // find the inorder successor and copy it to the root node
		root->value = minNode->value;
		root->right = delete(root->right, minNode->value); // delete the node we copied from
	}
	return root;
}

Node* find_min_node(Node* root) // get the smallest node in the left subtree of the right child of root
{
	Node* current = root;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

int free_tree(Node* root)
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

Node* generate_tree()
{
    Node* root = (Node*)(malloc(sizeof(Node)));
    root->value = 76;
    root->left = NULL;
    root->right = NULL;
	root = insert(root, 50);
	root = insert(root, 90);
	root = insert(root, 39);
	root = insert(root, 60);
	root = insert(root, 87);
	root = insert(root, 124);
    return root;
}
