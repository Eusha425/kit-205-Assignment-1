// hashtable_wk5.c
#include <stdlib.h>
#include "hashtable_wk5.h"
#include <string.h>
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS

HashTable create_hashtable(int n) {
	HashTable newtable;

	// TODO: allocate memory for array and init lists
	newtable.size = n;
	newtable.table = malloc(n * sizeof * newtable.table);

	for (int i = 0; i < n; i++)
	{
		newtable.table[i] = new_list();
	}

	return newtable;
}

int hash(String key, int size) {
	unsigned long h = 0; // unsigned long, so that when it wraps it's still positive
	int n = strlen(key);

	for (int i = 0; i < n; i++) {
		// multiply by 32 (<<5) and add ascii value
		h = (h << 5) + (int)(key[i]);
	}
	return h % size;
}

// Calculate the Jaccard similarity between two playlists
double calculate_similarity(List* playlist1, List* playlist2) {
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

void hash_insert(HashTable* self, String playlist_name, String song_name) {
	// 1. find the list to insert into using hash
	int hash_index = hash(playlist_name, self->size);

	// 2. call list function to insert into that list
	insert_at_front(&(self->table[hash_index]), song_name);
}

void hash_remove(HashTable* self, String playlist_name, String song_name) {
	// 1. find the list to remove from using hash
	int hash_index = hash(playlist_name, self->size);

	// 2. call list function to remove from that list
	delete_from_list(&(self->table[hash_index]), song_name);
}

void hash_print(HashTable* self, String playlist_name) {
	// 1. find the list to print using hash
	int hash_index = hash(playlist_name, self->size);

	// 2. call list function to print that list
	print_list(&(self->table[hash_index]));
}

int hash_count(HashTable* self, String song_name) {
	int count = 0;
	for (int i = 0; i < self->size; i++) {
		ListNodePtr current = self->table[i].head;
		while (current != NULL) {
			if (strstr(current->data, song_name) != NULL) {
				count++;
				break;
			}
			current = current->next;
		}
	}
	return count;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_wk5.h"

// Custom function to split a string by a delimiter and return the first part
char* split_string(const char* str, char delimiter) {
	int length = strlen(str);
	int i;

	// Find the position of the delimiter
	for (i = 0; i < length; i++) {
		if (str[i] == delimiter) {
			break;
		}
	}

	// Allocate memory for the result and copy characters before the delimiter
	char* result = (char*)malloc(i + 1);
	if (result != NULL) {
		for (int j = 0; j < i; j++) {
			result[j] = str[j];
		}
		result[i] = '\0';
	}

	return result;
}

char* hash_most_similar(HashTable* self, String playlist_name) {
	double max_iou_similarity = -1.0;
	char* most_similar = NULL;

	int hash_index = hash(playlist_name, self->size);
	ListNodePtr current = self->table[hash_index].head;

	while (current != NULL) {
		char* current_playlist = split_string(current->data, '-');
		if (current_playlist != NULL) {
			int intersection = 0;
			int union_size = 0;

			int current_playlist_length = strlen(current_playlist);

			for (int i = 0; i < self->size; i++) {
				ListNodePtr playlist = self->table[i].head;
				while (playlist != NULL) {
					char* other_playlist = split_string(playlist->data, '-');
					if (other_playlist != NULL) {
						if (strcmp(current_playlist, other_playlist) == 0) {
							intersection++;
						}
						union_size++;
						free(other_playlist); // Free memory allocated by split_string
					}
					playlist = playlist->next;
				}
			}

			// Calculate IOU similarity
			if (union_size > 0) {
				double iou_similarity = (double)intersection / union_size;
				if (iou_similarity > max_iou_similarity) {
					max_iou_similarity = iou_similarity;
					if (most_similar != NULL) {
						free(most_similar); // Free memory allocated by previous most_similar
					}
					most_similar = malloc(current_playlist_length + 1);
					strcpy(most_similar, current_playlist);
				}
			}

			free(current_playlist); // Free memory if not used as most similar
		}

		current = current->next;
	}

	return most_similar;
}

void hash_destroy(HashTable* self) {
	for (int i = 0; i < self->size; i++) {
		destroy_list(&(self->table[i]));
	}
	free(self->table);
	self->size = 0;
}