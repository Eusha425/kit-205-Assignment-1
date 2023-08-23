#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include <string.h>
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS

// create an empty bst
BST new_bst() {
	BST temp;
	temp.root = NULL;
	return temp;
}


// recursive function to find a value and return the containing node
BSTNodePtr find_bst_node(BSTNodePtr self, String n) {
	if (self == NULL || strcmp(n, self->data_item) == 0) { /* not present, or here */
		return self;
	}
	else if (strcmp(n , self->data_item) < 0) {
		return find_bst_node(self->left, n);
	}
	else {
		return find_bst_node(self->right, n);
	}
}

// find a value in the tree and return the node
BSTNodePtr find_bst(BST* self, String n) {
	return find_bst_node(self->root, n);
}

// recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, String playlistName) {
	int data_size = strlen(playlistName) + 1;
	if (self == NULL) {
		self = malloc(sizeof * self);
		// self->playlist_name = _strdup(playlistName); // Use _strdup here
		BSTNodePtr new_node = malloc(sizeof * new_node);
		new_node->data_item = malloc(sizeof * new_node->data_item * data_size);
		strcpy(new_node->data_item, playlistName);


		self->left = NULL;
		self->right = NULL;
		//self->song_list = new_list();
	}
	else if (strcmp(playlistName, self->data_item) <= 0) {
		self->left = insert_bst_node(self->left, playlistName);
	}
	else if (strcmp(playlistName, self->data_item) > 0) {
		self->right = insert_bst_node(self->right, playlistName);
	}
	return self;
}



// insert a value into the tree
void insert_bst(BST* self, String n) {
	self->root = insert_bst_node(self->root, n);
}

// helper function for delete
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// recursive function to delete a value
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
	if (self != NULL) {
		if (n == self->data_item) { // found item 
			if (self->left != NULL && self->right != NULL) {
				// two child case 
				BSTNodePtr successor = min_node(self->right);
				self->data_item = successor->data_item;
				self->right = delete_bst_node(self->right, self->data_item);
			}
			else { // one or zero child case 
				BSTNodePtr to_free = self;
				if (self->left) {
					self = self->left;
				}
				else {
					self = self->right;
				}
				free(to_free);
			}
		}
		else if (n < self->data_item) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
	}
	return self;
}

// delete a value from the tree
void delete_bst(BST* self, int n) {
	self->root = delete_bst_node(self->root, n);
}

// recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %d ", self->data_item);
		print_in_order_bst_node(self->right);
		printf(")");
	}
}

// print the tree in order
void print_in_order_bst(BST* self) {
	print_in_order_bst_node(self->root);
}


int find_height_bst_node(BSTNodePtr self)
{
	int max;

	if (self == NULL) {
		return -1;
	}
	else
	{
		int left_height = find_height_bst_node(self->left);

		int right_height = find_height_bst_node(self->right);

		if (left_height > right_height)
		{
			max = left_height + 1;
			return max;
		}
		else
		{
			max = right_height + 1;
			return max;
		}
	}
}

// print height of the tree
void print_height_bst(BST* self)
{
	printf("%d", find_height_bst_node(self->root));
}

// recursive function to detroy all node
void destroy_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		destroy_bst_node(self->left);
		self->left = NULL;
		destroy_bst_node(self->right);
		self->right = NULL;
		free(self);
	}
}

// destroy the tree
void destroy_bst(BST* self) {
	destroy_bst_node(self->root);
	self->root = NULL;
}

void bst_test() {
	BST tree = new_bst();
	int quit = 0;
	int data;
	while (quit == 0) {
		printf("Enter some data: ");
		scanf_s("%d", &data);
		if (data != 0) {
			insert_bst(&tree, data);
		}
		else {
			quit = 1;
		}
	}/*
	printf("Tree in order: \n");
	print_in_order_bst(&tree);
	printf("\nTree pre order: \n");
	print_pre_order_bst(&tree);
	printf("\nTree post order: \n");
	print_post_order_bst(&tree);
	printf("\nTree height: \n");
	print_height_bst(&tree);
	printf("\n");
	*/
	delete_bst(&tree, 9);
	delete_bst(&tree, 11);
	delete_bst(&tree, 6);
	delete_bst(&tree, 12);
	delete_bst(&tree, 10);
	printf("\nTree pre order: \n");


}