// hashtable_wk5.c
#include <stdlib.h>
#include "hashtable_wk5.h"

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

void hash_insert(HashTable* self, String key) {
	// TODO

	// 1. find the list to insert into using hash
	int hash_index = hash(key, self->size);

	// 2. call list function to insert into that list
	insert_at_front(&(self->table[hash_index]), key);
}

void hash_remove(HashTable* self, String key) {
	// TODO
	int hash_index = hash(key, self->size);
	delete_from_list(&(self->table[hash_index]), key);
}

void hash_print(HashTable* self) {
	for (int i = 0; i < self->size; i++) {
		printf("%d: ", i);
		print_list(&(self->table[i]));
	}
}

void hash_destroy(HashTable* self) {
	// TODO

	for (int i = 0; i < self->size; i++)
	{
		destroy_list(&(self->table[i]));
	}

	free(self->table);
	self->size = 0;

}