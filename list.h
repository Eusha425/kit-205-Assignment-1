// list.h
#pragma once

//TODO: change data type to char*
//Hint: use following typedef to make code clearer
typedef char* String;

typedef struct listNode {
	String data;
	struct listNode* next;
} *ListNodePtr;

typedef struct list {
	ListNodePtr head;
} List;


List new_list();

void print_list(List* self);

void insert_at_front(List* self, String data);

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, String data);

void delete_from_list(List* self, String data);

void destroy_list(List* self);