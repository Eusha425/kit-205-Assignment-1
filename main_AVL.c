// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"  // Include your AVL tree implementation

#pragma warning(disable : 4996)  // to suppress CRT SECURE NO WARNINGS

// Function to find the most similar playlist
void find_most_similar_playlist_avl(AVL* playlist_tree, String target_playlist) {
    AVLNodePtr target_node = find_avl(playlist_tree, target_playlist);
    if (target_node == NULL) {
        printf("Playlist '%s' not found.\n", target_playlist);
        return;
    }

    double max_similarity = -1.0;
    String most_similar_playlist = NULL;

    AVLNodePtr current_node = playlist_tree->root;
    while (current_node != NULL) {
        if (strcmp(current_node->data_item, target_playlist) != 0) {
            double similarity = calculate_jaccard_similarity_avl(&(current_node->song), &(target_node->song));
            if (similarity > max_similarity) {
                max_similarity = similarity;
                most_similar_playlist = current_node->data_item;
            }
        }
        current_node = (strcmp(target_playlist, current_node->data_item) < 0) ? current_node->left : current_node->right;
    }

    if (most_similar_playlist != NULL) {
        printf("The most similar playlist to '%s' is '%s' with Jaccard similarity %.2lf\n", target_playlist, most_similar_playlist, max_similarity);
    }
    else {
        printf("No similar playlists found for '%s'.\n", target_playlist);
    }
}

int main() {
    AVL playlist_tree = new_avl();

    int choice;
    String playlist_buffer[100];  // Initialize with memory for playlist name
    String song_buffer[100];      // Initialize with memory for song name
    String target_playlist[100];

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
            insert_avl(&playlist_tree, playlist_buffer, song_buffer);
            break;

        case 2:
            printf("Enter playlist name: ");
            scanf("%s", playlist_buffer);
            printf("Enter song name: ");
            scanf("%s", song_buffer);

            // Find the playlist from which the song is to be removed
            AVLNodePtr find_song_playlist = find_avl(&playlist_tree, playlist_buffer);
            delete_from_list_avl(&(find_song_playlist->song), song_buffer);
            break;

        case 3:
            printf("Enter the playlist name:");
            scanf("%s", playlist_buffer);

            // Find the playlist which needs to be displayed
            AVLNodePtr find_playlist = find_avl(&playlist_tree, playlist_buffer);
            print_list_avl(&(find_playlist->song));
            break;

        case 4:
            printf("Enter song name: ");
            scanf("%s", song_buffer);
            int playlistCount = count_playlists_with_song_avl(playlist_tree.root, song_buffer);
            printf("The song '%s' appears in %d playlists.\n", song_buffer, playlistCount);
            break;

        case 5:
            // Find most similar playlist
            printf("Enter the playlist name for recommendations: ");
            scanf("%s", target_playlist);
            find_most_similar_playlist_avl(&playlist_tree, target_playlist);
            break;

        case 0:
            destroy_avl(&playlist_tree);
            break;

        default:
            printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}
