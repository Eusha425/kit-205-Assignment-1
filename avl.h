// avl.h
#pragma once
#include "list_avl.h"

// Typedef for AVL tree node
typedef struct avlNode {
    String data_item;
    List song;
    struct avlNode* left;
    struct avlNode* right;
    int height;  // Height of the node
} *AVLNodePtr;

// Typedef for AVL tree
typedef struct avl {
    AVLNodePtr root;
} AVL;

AVL new_avl();

AVLNodePtr find_avl(AVL* self, String playlist);

void insert_avl(AVL* self, String playlist, String song);

void delete_avl(AVL* self, String playlist);

void print_in_order_avl(AVL* self);

void destroy_avl(AVL* self);

int count_playlists_with_song_avl(AVLNodePtr root, String song_name);

double calculate_jaccard_similarity_avl(List* playlist1, List* playlist2);


