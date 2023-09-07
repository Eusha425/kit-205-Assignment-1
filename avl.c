// bst.c
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include <string.h>
#include "list_avl.h"
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS

// create an empty bst
AVL new_avl() {
	AVL temp;
	temp.root = NULL;
	return temp;
}

// Recursive function to find a node with a given data item in an AVL tree
AVLNodePtr find_avl_node(AVLNodePtr self, String data) {
	if (self == NULL || strcmp(data, self->data_item) == 0) {
		return self;
	}
	else if (strcmp(data, self->data_item) < 0) {
		return find_avl_node(self->left, data);
	}
	else {
		return find_avl_node(self->right, data);
	}
}

// find a value in the tree and return the node
AVLNodePtr find_avl(AVL* self, String playlist) {
	return find_avl_node(self->root, playlist);
}

// Function to calculate the height of a node
int node_height(AVLNodePtr node) {
	if (node == NULL) {
		return -1;
	}
	return node->height;
}

// Function to calculate the maximum of two integers
int max_int(int a, int b) {
	return (a > b) ? a : b;
}

// Function to perform a left rotation
AVLNodePtr left_rotate(AVLNodePtr node) {
	AVLNodePtr new_root = node->right;
	node->right = new_root->left;
	new_root->left = node;

	// Update heights
	node->height = max_int(node_height(node->left), node_height(node->right)) + 1;
	new_root->height = max_int(node_height(new_root->left), node_height(new_root->right)) + 1;

	return new_root;
}

// Function to perform a right rotation
AVLNodePtr right_rotate(AVLNodePtr node) {
	AVLNodePtr new_root = node->left;
	node->left = new_root->right;
	new_root->right = node;

	// Update heights
	node->height = max_int(node_height(node->left), node_height(node->right)) + 1;
	new_root->height = max_int(node_height(new_root->left), node_height(new_root->right)) + 1;

	return new_root;
}

// Function to balance a node if it violates the AVL balance property
AVLNodePtr balance_node(AVLNodePtr node) {
	int balance = node_height(node->left) - node_height(node->right);

	// Left heavy
	if (balance > 1) {
		// Left-Left (LL) case
		if (strcmp(node->data_item, node->left->data_item) < 0) {
			return right_rotate(node);
		}
		// Left-Right (LR) case
		else {
			node->left = left_rotate(node->left);
			return right_rotate(node);
		}
	}
	// Right heavy
	else if (balance < -1) {
		// Right-Right (RR) case
		if (strcmp(node->data_item, node->right->data_item) > 0) {
			return left_rotate(node);
		}
		// Right-Left (RL) case
		else {
			node->right = right_rotate(node->right);
			return left_rotate(node);
		}
	}

	// No balancing needed
	return node;
}

// recursive function to insert a value
AVLNodePtr insert_avl_node(AVLNodePtr self, String playlist_name, String song_name) {
	// Perform regular BST insertion
	if (self == NULL) {
		AVLNodePtr new_node = malloc(sizeof * new_node);
		if (new_node == NULL) {
			// Handle memory allocation failure if needed
			return NULL;
		}

		// Allocate memory for data_item and copy playlist_name
		new_node->data_item = malloc(strlen(playlist_name) + 1);
		if (new_node->data_item == NULL) {
			// Handle memory allocation failure if needed
			free(new_node);
			return NULL;
		}
		strcpy(new_node->data_item, playlist_name);

		// Initialize other fields
		new_node->song = new_list_avl();
		insert_in_order_avl(&(new_node->song), song_name);
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->height = 0;
		return new_node;
	}

	// Recursively insert into the appropriate subtree
	if (strcmp(playlist_name, self->data_item) < 0) {
		self->left = insert_avl_node(self->left, playlist_name, song_name);
	}
	else if (strcmp(playlist_name, self->data_item) > 0) {
		self->right = insert_avl_node(self->right, playlist_name, song_name);
	}
	else {
		// Playlist already exists, insert the song
		insert_in_order(&(self->song), song_name);
		return self;
	}

	// Update the height of the current node
	self->height = max_int(node_height(self->left), node_height(self->right)) + 1;

	// Balance the current node
	return balance_node(self);
}

void insert_avl(AVL* self, String playlist, String song) {
	self->root = insert_avl_node(self->root, playlist, song);
}

// Helper function to find the minimum node in a subtree
AVLNodePtr find_min_node(AVLNodePtr node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}


// Recursive function to delete a node from an AVL tree
AVLNodePtr delete_avl_node(AVLNodePtr self, String data) {
	if (self == NULL) {
		return self;
	}

	// Recursively delete from the appropriate subtree
	if (strcmp(data, self->data_item) < 0) {
		self->left = delete_avl_node(self->left, data);
	}
	else if (strcmp(data, self->data_item) > 0) {
		self->right = delete_avl_node(self->right, data);
	}
	else {
		// Node with the data to be deleted found

		// Node with only one child or no child
		if (self->left == NULL || self->right == NULL) {
			AVLNodePtr temp = self->left ? self->left : self->right;

			// No child case
			if (temp == NULL) {
				temp = self;
				self = NULL;
			}
			else {
				// Copy the contents of the non-empty child
				self->data_item = temp->data_item;
				self->song = temp->song;
				self->left = temp->left;
				self->right = temp->right;
				self->height = temp->height;
			}
			free(temp);
		}
		else {
			// Node with two children, get the inorder successor
			AVLNodePtr temp = find_min_node(self->right);

			// Copy the inorder successor's data to this node
			self->data_item = temp->data_item;
			self->song = temp->song;

			// Delete the inorder successor
			self->right = delete_avl_node(self->right, temp->data_item);
		}
	}

	if (self == NULL) {
		return self;
	}

	// Update the height of the current node
	self->height = max_int(node_height(self->left), node_height(self->right)) + 1;

	// Balance the current node
	return balance_node(self);
}


void delete_avl(AVL* self, String data) {
	self->root = delete_avl_node(self->root, data);
}

// recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %s ", self->data_item);
		print_in_order_bst_node(self->right);
		printf(")");
	}
}

// print the tree in order
void print_in_order_bst(BST* self) {
	print_in_order_bst_node(self->root);
}


/*
void test_playlist(BSTNodePtr self, String playlist_name)
{
	BSTNodePtr find_playlist = find_bst(self, playlist_name);
	print_list(&(find_playlist));
}
*/

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

// Count the number of playlists that a song appears in
int count_playlists_with_song(BSTNodePtr root, String song_name) {
	if (root == NULL) {
		return 0;
	}

	int count = count_occurrences(&(root->song), song_name);

	int left_count = count_playlists_with_song(root->left, song_name);
	int right_count = count_playlists_with_song(root->right, song_name);

	return count + left_count + right_count;
}

// Function to calculate Jaccard similarity between two playlists
double calculate_jaccard_similarity(List* playlist1, List* playlist2) {
	int intersection = 0;
	int union_size = 0;

	ListNodePtr current1 = playlist1->head;
	while (current1 != NULL) {
		ListNodePtr current2 = playlist2->head;
		while (current2 != NULL) {
			if (strcmp(current1->data, current2->data) == 0) {
				intersection++;
				break;
			}
			current2 = current2->next;
		}
		union_size++;
		current1 = current1->next;
	}

	return (double)intersection / union_size;
}