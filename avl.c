// bst.c
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include <string.h>
#include "list.h"
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


// recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, String playlist_name, String song_name) {
	int data_size = strlen(playlist_name) + 1;
	if (self == NULL) {
		self = malloc(sizeof * self);
		// self->playlist_name = _strdup(playlistName); // Use _strdup here

		BSTNodePtr new_node = malloc(sizeof * new_node);
		new_node->data_item = malloc(sizeof * new_node->data_item * data_size);
		strcpy(new_node->data_item, playlist_name);
		List list_song = new_list();
		// insert_at_front(&list_song, song_name);
		insert_in_order(&list_song, song_name);
		new_node->song = list_song;

		self = new_node;

		self->left = NULL;
		self->right = NULL;
		//self->song_list = new_list();
	}
	else if (strcmp(playlist_name, self->data_item) == 0) {
		// insert_at_front(&self->song, song_name);
		insert_in_order(&self->song, song_name);
	}
	else if (strcmp(playlist_name, self->data_item) < 0) {
		self->left = insert_bst_node(self->left, playlist_name, song_name);
	}
	else if (strcmp(playlist_name, self->data_item) > 0) {
		self->right = insert_bst_node(self->right, playlist_name, song_name);
	}
	return self;
}

// insert a value into the tree
void insert_bst(BST* self, String playlist, String song) {
	self->root = insert_bst_node(self->root, playlist, song);
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
BSTNodePtr delete_bst_node(BSTNodePtr self, String data) {
	if (self != NULL) {
		int compareResult = strcmp(data, self->data_item);
		if (compareResult == 0) { // found item
			if (self->left != NULL && self->right != NULL) {
				// two child case
				BSTNodePtr successor = min_node(self->right);
				free(self->data_item);
				strcpy(self->data_item, successor->data_item);
				//self->data_item = strdup(successor->data_item);
				self->right = delete_bst_node(self->right, successor->data_item);
			}
			else { // one or zero child case
				BSTNodePtr to_free = self;
				if (self->left) {
					self = self->left;
				}
				else {
					self = self->right;
				}
				free(to_free->data_item);
				free(to_free);
			}
		}
		else if (compareResult < 0) {
			self->left = delete_bst_node(self->left, data);
		}
		else {
			self->right = delete_bst_node(self->right, data);
		}
	}
	return self;
}

// delete a value from the tree
void delete_bst(BST* self, String data) {
	self->root = delete_bst_node(self->root, data);
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