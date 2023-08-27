#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"   // Include your binary search tree implementation
//#include "list.h"
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS
//main.c

void print_song_list(BST* self, String playlist)
{
    BSTNodePtr list = find_bst(self, playlist);
    print_song_playlist(list);
    
}

int main() {

    //bst_test();

    
    BST playlistTree = new_bst();

    int choice;
    String playlistBuffer[100]; // Initialize with memory for playlist name
    String songBuffer[100];     // Initialize with memory for song name


    do {
        printf("\n1. Add a song to a playlist\n");
        printf("2. Remove a song from a playlist\n");
        printf("3. Print songs in a playlist\n");
        printf("4. Count playlists that a song appears in\n");
        printf("5. Find most similar playlist\n");
        printf("0. Quit\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter playlist name: ");
            scanf("%s", playlistBuffer);
            printf("Enter song name: ");
            scanf("%s", songBuffer);
            insert_bst(&playlistTree, playlistBuffer, songBuffer);

            // Check if playlist already exists in the tree
            /*
            BSTNodePtr existingPlaylist = find_bst(&playlistTree, playlistName);
            if (existingPlaylist == NULL) {
                // Create new playlist node
                BSTNodePtr newPlaylist = malloc(sizeof*newPlaylist);
                newPlaylist->playlist_name = strdup(playlistName);
                newPlaylist->left = newPlaylist->right = NULL;
                newPlaylist->song_list = new_list();
                insert_bst(&playlistTree, newPlaylist);
            }
            */

            // Add song to the playlist's song list
            // BSTNodePtr playlistNode = find_bst(&playlistTree, playlistName);
            // insert_at_front(&playlistNode->song_list, songName);
            
            break;

            // Implement other cases here
        case 2:
            printf("Enter playlist name to delete: ");
            scanf("%s", playlistBuffer);
            delete_bst(&playlistTree, playlistBuffer);
            //find_bst(&playlistTree, playlistBuffer);
            break;

        case 3:
            
            printf("The tree in order:");

            scanf("%s", &playlistBuffer);


            
            //print_in_order_bst(&playlistTree);
            print_song_list(&playlistTree, playlistBuffer);

            break;
        case 0:
            // Clean up and exit
            // destroy_bst(&playlistTree);
            printf("\nExiting...\n");
            break;

        default:
            printf("Invalid choice\n");
        }
        
    } while (choice != 0);
    

    return 0;
}