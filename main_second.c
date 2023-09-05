// main.c
#include <stdio.h>
#include "list_wk5.h"
#include "hashtable_wk5.h"
#pragma warning(disable:4996) // to suppress CRT SECURE NO WARNINGS


// Find the most similar playlist for recommendations
char* find_most_similar_playlist_hash(HashTable* table, String target_playlist) {
    double max_similarity = -1.0;
    char* most_similar = NULL;

    // Calculate similarity between the target playlist and all other playlists
    int target_index = hash(target_playlist, table->size);
    List* target_list = &(table->table[target_index]);

    for (int i = 0; i < table->size; i++) {
        if (i != target_index) {
            List* current_list = &(table->table[i]);

            // Check if the current list is empty before accessing its head
            if (current_list->head != NULL) {
                double similarity = calculate_similarity(target_list, current_list);

                if (similarity > max_similarity) {
                    max_similarity = similarity;
                    most_similar = current_list->head->playlist_name;
                }
            }
        }
    }
    return most_similar;
}


int main() {
    int command = 1;
    HashTable table = create_hashtable(11);
    char buffer[100];

    while (command) {
        // menu for easier user interaction
        printf("Press 1 to add a song to a playlist\n");
        printf("Press 2 to remove a song from a playlist\n");
        printf("Press 3 to print songs in a playlist in alphabetical order\n");
        printf("Press 4 to find the number of playlists a song appears in\n");
        printf("Press 5 to find the most similar playlist for recommendations\n");
        printf("Press 0 to exit\n");
        scanf("%d", &command);

        switch (command) {
        case 1:
        {
            char playlist_name[100];
            char song_name[100];
            scanf("%s", playlist_name);
            scanf("%s", song_name);
            hash_insert(&table, playlist_name, song_name);
            break;
        }
        case 2:
        {
            char playlist_name[100];
            char song_name[100];
            scanf("%s", playlist_name);
            scanf("%s", song_name);
            hash_remove(&table, playlist_name, song_name);
            break;
        }
        case 3:
        {
            char playlist_name[100];
            scanf("%s", playlist_name);
            hash_print(&table, playlist_name);
            break;
        }

        case 4:
        {
            char song_name[100];
            scanf("%s", song_name);
            int count = hash_count(&table, song_name);
            printf("Song %s appears in %d playlist(s).\n", song_name, count);
            break;
        }
        case 5:
        {
            char playlist_name[100];
            scanf("%s", playlist_name);
            char* most_similar = find_most_similar_playlist_hash(&table, playlist_name);
            printf("The most similar playlist to %s is %s.\n", playlist_name, most_similar);
            break;
        }
        case 0:
            // Exit the program
            break;
        default:
            printf("Invalid command\n");
        }
        printf("\n");
    }
    // Cleanup and destroy the hashtable
    hash_destroy(&table);

    return 0;
}
