#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"   // Include your binary search tree implementation
//#include "list.h"
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS
//main.c



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
            
            break;
        case 2:
            
            printf("Enter playlist name: ");
            scanf("%s", playlistBuffer);
            printf("Enter song name: ");
            scanf("%s", songBuffer);
            BSTNodePtr find_song_playlist = find_bst(&playlistTree, playlistBuffer);
            delete_from_list(&find_song_playlist->song, songBuffer);
            
            break;

        case 3:
            
            printf("Enter the playlist name:");
            scanf("%s", &playlistBuffer);

            // find the playlist, from user input name
            BSTNodePtr find_playlist = find_bst(&playlistTree, playlistBuffer);
            print_list(&(find_playlist->song));

            break;
        case 0:

            // Clean up and exit
            destroy_bst(&playlistTree);
            printf("\nExiting...\n");
            break;

        default:
            printf("Invalid choice\n");
        }
        
    } while (choice != 0);
    

    return 0;
}
