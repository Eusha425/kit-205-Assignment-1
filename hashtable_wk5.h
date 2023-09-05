// hashtable_wk5.h
#pragma once

#include "list_wk5.h"

typedef struct hashTable {
    int size;
    List* table;
} HashTable;

HashTable create_hashtable(int n);

int hash(String key, int size);

void hash_insert(HashTable* self, String playlist_name, String song_name);

void hash_remove(HashTable* self, String playlist_name, String song_name);

void hash_print(HashTable* self, String playlist_name);

int hash_count(HashTable* self, String song_name);

char* hash_most_similar(HashTable* self, String playlist_name);

double calculate_similarity(List* playlist1, List* playlist2);

void hash_destroy(HashTable* self);
