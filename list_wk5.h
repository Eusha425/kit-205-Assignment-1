// list_wk5.h
#pragma once

typedef char* String;

typedef struct listNode {
    String playlist_name;
    String data;
    struct listNode* next;
} *ListNodePtr;


typedef struct list {
    ListNodePtr head;
} List;

List new_list_hash();

void print_list_hash(List* self);

void insert_at_front_hash(List* self, String playlist_name, String data);

// void insert_at_front(List* self, String data);

void delete_from_list_hash(List* self, String data);

void destroy_list_hash(List* self);
