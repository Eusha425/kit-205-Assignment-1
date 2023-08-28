#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"   // Include your binary search tree implementation
//#include "list.h"
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS
//main.c



int main() {

    BST playlist_tree = new_bst();

    int choice;
    String playlist_buffer[100]; // Initialize with memory for playlist name
    String song_buffer[100];     // Initialize with memory for song name


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
            scanf("%s", playlist_buffer);
            printf("Enter song name: ");
            scanf("%s", song_buffer);
            insert_bst(&playlist_tree, playlist_buffer, song_buffer);
            
            break;
        case 2:
            
            printf("Enter playlist name: ");
            scanf("%s", playlist_buffer);
            printf("Enter song name: ");
            scanf("%s", song_buffer);

            // find the playlist from which the song is to be removed
            BSTNodePtr find_song_playlist = find_bst(&playlist_tree, playlist_buffer); 
            delete_from_list(&find_song_playlist->song, song_buffer);
            
            break;

        case 3:
            
            printf("Enter the playlist name:");
            scanf("%s", &playlist_buffer);

            // find the playlist which needs to be displayed
            BSTNodePtr find_playlist = find_bst(&playlist_tree, playlist_buffer);
            print_list(&(find_playlist->song));

            break;
        case 0:

            // Clean up and exit
            destroy_bst(&playlist_tree);
            printf("\nExiting...\n");
            break;

        default:
            printf("Invalid choice\n");
        }
        
    } while (choice != 0);
    

    return 0;
}
