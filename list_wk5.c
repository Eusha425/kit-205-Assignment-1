// list_wk5.c
#include <stdio.h>
#include <stdlib.h>
#include "list_wk5.h"
#include <string.h>
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS

//TODO: change data type to char*

List new_list_hash() {
	List temp;
	temp.head = NULL;
	return temp;
}

void print_list_hash(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%s\n", current->data); // Add '\n' here
		current = current->next;
	}
}


// after changing to char*:
// -- need to change printf for string
void print_list_hash1(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%s", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

void insert_in_order_hash(List* self, String playlist_name, String data) {
	ListNodePtr new_node = malloc(sizeof(struct listNode));

	if (new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Allocate memory for playlist_name and data
	new_node->playlist_name = malloc(strlen(playlist_name) + 1);
	new_node->data = malloc(strlen(data) + 1);

	if (new_node->playlist_name == NULL || new_node->data == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Copy the strings into the new node
	strcpy(new_node->playlist_name, playlist_name);
	strcpy(new_node->data, data);

	// If the list is empty or the new node should be inserted at the front
	if (self->head == NULL || strcmp(data, self->head->data) < 0) {
		new_node->next = self->head;
		self->head = new_node;
	}
	else {
		// Traverse the list to find the correct position
		ListNodePtr current = self->head;
		ListNodePtr prev = NULL;

		while (current != NULL && strcmp(data, current->data) >= 0) {
			prev = current;
			current = current->next;
		}

		// Insert the new node between prev and current
		prev->next = new_node;
		new_node->next = current;
	}
}


// Insert a new node with data at the front of the list
void insert_at_front_hash(List* self, String playlist_name, String data) {
	ListNodePtr new_node = malloc(sizeof(struct listNode));

	if (new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Allocate memory for playlist_name and data
	new_node->playlist_name = malloc(strlen(playlist_name) + 1);
	new_node->data = malloc(strlen(data) + 1);

	if (new_node->playlist_name == NULL || new_node->data == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Copy the strings into the new node
	strcpy(new_node->playlist_name, playlist_name);
	strcpy(new_node->data, data);

	new_node->next = self->head;
	self->head = new_node;
}

// Delete a node with the specified data from the list
void delete_from_list_hash(List* self, String data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (strcmp(current->data, data) == 0) {
			if (prev == NULL) { // Front of the list
				self->head = current->next;
				free(current->playlist_name);
				free(current->data);
				free(current);
				current = self->head;
			}
			else { // Middle or end of the list
				prev->next = current->next;
				free(current->playlist_name);
				free(current->data);
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}


// after changing to char*:
// -- need to free memory allocated for string before freeing node
void destroy_list_hash(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;

		current = current->next;
		free(to_free->data);
		free(to_free);
	}
	self->head = NULL;
}