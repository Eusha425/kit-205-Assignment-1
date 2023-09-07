// list_avl.h
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


List new_list_avl();

void print_list_avl(List* self);


// Function to insert a new node with given data in the list in ascending order.
void insert_in_order_avl(List* self, String data);

void delete_from_list_avl(List* self, String data);

void destroy_list_avl(List* self);