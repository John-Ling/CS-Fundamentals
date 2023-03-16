#include <stdio.h>
#include <stdlib.h>

// implementation of a binary search tree for learning purposes

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

int main(void)
{
    node* root = generate_tree();

	inorder_traversal(root);
    search_tree(root, 39);
    free_tree(root);
    return 0;
}

void inorder_traversal(node* root)
{
    if (root == NULL)
        return;
    inorder_traversal(root->left); // visit all nodes to the left
    printf("%i\n", root->value); // visit root node
    inorder_traversal(root->right); // visit all nodes to the right
}

void search_tree(node* root, int value)
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

node* insert(node* root, int value)
{
	if (root != NULL)
	{
		if (value > root->value)
		{
			if (root != NULL)
			{
				printf("Calling function for left node\n");
				insert(root->left, value);
			}
			else 
			{
				printf("Adding node to left\n");
				node* node = malloc(sizeof(node));
				node->value = value;
				node->left = NULL;
				node->right = NULL;
				root->left = node;
				return root;
			}
		}
		else if (value < root->value)
		{
			if (root != NULL)
			{
				printf("Calling function for right node\n");
				insert(root->right, value);
			}
			else
			{
				printf("Adding node to right\n");
				node* node = malloc(sizeof(node));
				node->value = value;
				node->left = NULL;
				node->right = NULL;
				root->right = node;
				return root;
			}
		}
	}
}


void free_tree(node* root)
{
    // free allocated memory using postorder traversal left --> right --> root
    if (root == NULL)
        return;
    
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

node* generate_tree()
{
    node* root = malloc(sizeof(node));
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