# C Playlist Prototype 

This repository contains a C console application that serves as a prototype for a database designed to manage user playlists. The application facilitates operations such as adding and removing songs from playlists, printing playlist contents, determining song popularity, and recommending similar playlists.

## Functionality

The application offers the following functionalities:

- **Add Song to Playlist:** Allows users to add a song to a specified playlist.
- **Remove Song from Playlist:** Enables users to remove a song from a specified playlist.
- **Print Playlist Contents:** Prints the songs within a given playlist in alphabetical order.
- **Find Song Popularity:** Displays the number of playlists a song appears in.
- **Recommend Similar Playlist:** Identifies the playlist most similar to a given playlist using Jaccard similarity.

## Input/Output

Users interact with the application by entering a number corresponding to the desired operation from the list above. Entering '0' exits the application. All user input is assumed to be valid and logical. Output is kept minimal to ease code inspection.

## Data Structures

The prototype utilizes Binary Search Trees (BST) with linked lists and AVL trees with linked lists for storing and manipulating playlists and songs.

## Testing

The repository includes unit tests for the implemented data structures and the overall program for verification purposes. Additionally, performance testing is conducted using pre-generated test files to analyze asymptotic performance.

## Report

A separate report outlines the chosen data structures, justifications, and reasoning behind the selected implementations for comparison. It also discusses the testing methodologies employed.
