#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "PlaylistNode.h"

/*
* main.c file for Lab 9
* April Clark
* Date: 3/12/22
*/

// BufferPurge method
void BufferPurge(void)
{
    char c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

char PrintMenu(char playlistTitle[]);
void AddSong(PlaylistNode **head, PlaylistNode **tail);
void RemoveSong(PlaylistNode **head, PlaylistNode **tail);
void ChangeSongPosition(PlaylistNode **head, PlaylistNode **tail);
void OutputSpecificArtist(PlaylistNode *head);
void OutputTotalTime(PlaylistNode *head);
void OutputThePlaylist(PlaylistNode *head, char playlistTitle[]);

// Main method
int main(void) {
    // create playlist title array
    char playlistTitle[50];
    char selection;
    PlaylistNode *head = NULL;
    PlaylistNode *tail = NULL;

    // get playlist title
    printf("Enter playlist's title:\n");
    fgets(playlistTitle, 50, stdin);
    playlistTitle[strlen(playlistTitle) - 1] = '\0';

    // Menu selection
    while (selection != 'q') {
        selection = PrintMenu(playlistTitle);
        if (selection == 'a') {
            AddSong(&head, &tail);
        }
        else if (selection == 'r') {
            RemoveSong(&head, &tail);
        }
        else if (selection == 'c') {
            ChangeSongPosition(&head, &tail);
        }
        else if (selection == 's') {
            OutputSpecificArtist(head);
        }
        else if (selection == 't') {
            OutputTotalTime(head);
        }
        else if (selection == 'o') {
            OutputThePlaylist(head, playlistTitle);
        }
        printf("\n");
        
    }
    return 0;
}

// Print Menu - outputs the menu options 
// & takes in the user option
char PrintMenu(char playlistTitle[]) {

    char option;

    // Choices output
    printf("%s PLAYLIST MENU\n", playlistTitle);
    printf("a - Add song\n");
    printf("r - Remove song\n");
    printf("c - Change position of song\n");
    printf("s - Output songs by specific artist\n");
    printf("t - Output total time of playlist (in seconds)\n");
    printf("o - Output full playlist\n");
    printf("q - Quit\n");
    printf("\nChoose an option: ");
    scanf(" %c", &option);
    BufferPurge();
    option = tolower(option);

    // handles the user option
    while (option != 'a' && option != 'r' && option != 'c' && option != 's' && option != 't' && option != 'o' && option != 'q') {
        printf("Please choose a valid menu option\n");
        scanf(" %c", &option);
        BufferPurge();
        option = tolower(option); // only accept lowercase
    }
    return option;
}

// AddSong function
void AddSong(PlaylistNode **head, PlaylistNode **tail) {
    char uniqueID[50];
    char songName[50];
    char artistName[50];
    int songLength;

    // add song input
    printf("\nADD SONG\n");
    printf("Enter song's unique ID:\n");
    fgets(uniqueID, 50, stdin);
    uniqueID[strlen(uniqueID) - 1] = '\0';
    printf("Enter song's name:\n");
    fgets(songName, 50, stdin);
    songName[strlen(songName) - 1] = '\0';
    printf("Enter artist's name:\n");
    fgets(artistName, 50, stdin);
    artistName[strlen(artistName) - 1] = '\0';
    printf("Enter song's length (in seconds):\n");
    scanf(" %d", &songLength);
    BufferPurge();

    // Set-up for node with params
    PlaylistNode *node = CreatePlaylistNode(uniqueID, songName, artistName, songLength);
    if (node != NULL) {
        if (*head == NULL) {
            *head = node;
        }
        else {
            SetNextPlaylistNode(*tail, node);
        }
        *tail = node;
    }
    else {
        printf("Error!\n");
    }
}

// Remove Song function
// only accepts a valid song in the list
void RemoveSong(PlaylistNode **head, PlaylistNode **tail) {
    char uniqueID[50];

    // get the ID of the song to remove
    printf("\nREMOVE SONG\n");
    printf("Enter song's unique ID:\n");
    fgets(uniqueID, 50, stdin);
    uniqueID[strlen(uniqueID) - 1] = '\0';

    if (*head != NULL) {
        PlaylistNode *curr = *head;
        PlaylistNode *prev = NULL;

        // remove the song ID if matched in strcmp
        while (curr != NULL) {
            if (strcmp(curr->uniqueID, uniqueID) == 0) {
                break;
            }
            prev = curr;
            curr = GetNextPlaylistNode(curr);
        }
        if (curr != NULL) {
            if (prev == NULL) {
                *head = GetNextPlaylistNode(*head);
                if (*head == NULL) {
                    *tail = NULL;
                }
            }
            else {
                SetNextPlaylistNode(prev, GetNextPlaylistNode(curr));

                if (GetNextPlaylistNode(prev) == NULL) {
                    *tail = prev;
                }
            }
            printf("\"%s\" removed\n", curr->songName);
            DestroyPlaylistNode(curr);
        }
    }
    else {
        printf("No Song matches the ID: %s exists in the Playlist\n", uniqueID);
    }
}

// Change Song Position function
void ChangeSongPosition(PlaylistNode **head, PlaylistNode **tail) {
    int current_position;
    int new_position;
    int i = 0;

    // Get the current position and desired location.
    printf("\nCHANGE POSITION OF SONG\n");
    printf("Enter song's current position:\n");
    scanf("%d", &current_position);
    BufferPurge();
    printf("Enter new position for song:\n");
    scanf("%d", &new_position);
    BufferPurge();
    
    PlaylistNode *curr = *head;

    // update position
    while (curr != NULL) {
        i++;
        curr = GetNextPlaylistNode(curr);
    }

    // update to new positions
    if (current_position >= 1 && current_position <= i) {
        if (new_position < 1) {
            new_position = 1;
        }
        else if (new_position > i) {
            new_position = i;
        }
        if (current_position != new_position) {
            PlaylistNode *current;
            curr = *head;
            PlaylistNode *prev = NULL;
            int pos = 0;

            // Remove current position
            while (curr != NULL) {
                pos++;
                if (pos == current_position) {
                    current = curr;
                    if (prev == NULL) {
                        *head = GetNextPlaylistNode(*head);
                        if (GetNextPlaylistNode(*head) == NULL) {
                            *tail = *head;
                        }
                    }
                    else {
                        SetNextPlaylistNode(prev, GetNextPlaylistNode(curr));
                        if (GetNextPlaylistNode(prev) == NULL) {
                            *tail = prev;
                        }
                    }
                    break;
                }
                prev = curr;
                curr = GetNextPlaylistNode(curr);
            }
            // find node to insert new position
            SetNextPlaylistNode(current, NULL);
            curr = *head;
            prev = NULL;
            pos = 1;

            while ((curr != NULL) && (pos != new_position)) {
                prev = curr;
                curr = GetNextPlaylistNode(curr);
                pos++;
            }

            // Finalize the new node position
            SetNextPlaylistNode(current, curr);
            if (prev == NULL) {
                *head = current;
            }
            else if (curr == NULL) {
                SetNextPlaylistNode(*tail, current);
                *tail = current;
            }
            else {
                SetNextPlaylistNode(prev, current);
            }
            printf("\"%s\" moved to position %d\n", current->songName, new_position);
        }
    }
    else {
        printf("Error!\n");
    }
}

// Output Specific Artist function
void OutputSpecificArtist(PlaylistNode *head) {
    char artistName[50];
    
    printf("\nOUTPUT SONGS BY SPECIFIC ARTIST\n");
    printf("Enter artist's name:\n");
    fgets(artistName, 50, stdin);
    artistName[strlen(artistName) - 1] = '\0';
    PlaylistNode *curr = head;
    int pos = 1;

    // get all the artist's songs
    while (curr != NULL) {
        if (strcmp(curr->artistName, artistName) == 0) {
            printf("%d.\n", pos);
            PrintPlaylistNode(curr);
            printf("\n");
        }
        curr = GetNextPlaylistNode(curr);
        pos++;
    }
}

// Output Total Time function
// displays the added seconds of all tracks in list
void OutputTotalTime(PlaylistNode *head) {
    printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
    int total_time = 0;
    PlaylistNode *curr = head;

    // Calculates total time in seconds
    while (curr != NULL) {
        total_time += curr->songLength;
        curr = GetNextPlaylistNode(curr);
    }
    printf("Total time: %d seconds\n", total_time);
}

// Output Full Playlist function 
void OutputThePlaylist(PlaylistNode *head, char playlistTitle[]) {
    // Empty if null
    if (head == NULL) {
        printf("Please add songs for the playlist!\n");
    }
    else {
        PlaylistNode *curr = head;
        printf("%s - OUTPUT FULL PLAYLIST\n", playlistTitle);
        int pos = 1;
        
        // display all tracks
        while (curr != NULL)
        {
            printf("%d.\n", pos);
            PrintPlaylistNode(curr);
            printf("\n");
            curr = GetNextPlaylistNode(curr);
            pos++;
        }
    }
}
