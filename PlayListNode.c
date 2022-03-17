/*
* PlaylistNode.c which contains the main function calls for manipulating the playlist.
* 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PlaylistNode.h"

/* CreatePlaylistNode: Allocate a PlaylistNode in the heap using malloc
* the object will be initialized with the specified unique id, song name,
* artist name and song length. The nextNodePtr field will be set to NULL;
* id - NULL terminated string containing unique id
* songName - NULL terminated string containing the song name
* artistName - NULL terminated string containing the name of the artist
* songLength - int value with duration of song in seconds
*
* returns - Pointer to PlaylistNode allocated on the heap
*/

PlaylistNode *CreatePlaylistNode(char id[], char songName[], char artistName[], int songLength)
{

    PlaylistNode *node = (PlaylistNode *)malloc(sizeof(PlaylistNode));
    if (node != NULL)
    {
        // Nodes for 4 parameters in playlist creation.
        strcpy(node->uniqueID, id);
        strcpy(node->songName, songName);
        strcpy(node->artistName, artistName);
        node->songLength = songLength;
        node->nextNodePtr = NULL;
    }

    return node;
}

/* InsertPlaylistNodeAfter: Insert a new PlaylistNode into the linked list
* immediately after the specified node.
* nodeInList - Pointer to the PlaylistNode that the new PlaylistNode
* should be inserted after in the list
* newNode - Pointer to the new PlaylistNode to be added
* returns - 0 on success, -1 on error
*/

int InsertPlaylistNodeAfter(PlaylistNode *nodeInList, PlaylistNode *newNode)
{
    // If not null, newnode to next in list.
    if (nodeInList != NULL && newNode != NULL)
    {
        SetNextPlaylistNode(newNode, nodeInList->nextNodePtr);
        SetNextPlaylistNode(nodeInList, newNode);
    }
    else
    {
        printf("Error!\n");
        exit(0);
    }
    return 0;
}

/* SetNextPlaylistNode: Update the nextNodePtr field of the specified nodeInList
* to point to newNode. It is valid for newNode to be NULL, but not nodeInList.
* nodeInList - Pointer to PlaylistNode whose nextNodePtr field will be updated
* newNode - Pointer PlaylistNode to be set in the nextNodePtr
* returns - 0 on success, -1 on error
*/

int SetNextPlaylistNode(PlaylistNode *nodeInList, PlaylistNode *newNode)
{
    // If not null set next node to newnode.
    if (nodeInList != NULL)
    {
        nodeInList->nextNodePtr = newNode;
    }
    else
    {
        printf("Error!\n");
        exit(0);
    }
    return 0;
}

/* GetNextPlaylistNode: Return a pointer to the PlaylistNode that immediately
* follows the specified node in the list
* nodeInList - Pointer to PlaylistNode that we want to get the next node of
* returns - Pointer to next PlaylistNode, NULL on error or end of list
*/

PlaylistNode *GetNextPlaylistNode(PlaylistNode *nodeInList)
{
    if (nodeInList != NULL)
        return nodeInList->nextNodePtr;
    return NULL;
}

/* PrintPlaylistNode: Write the fields of the PlaylistNode, nicely formatted,
* to stdout (console) using printf.
* thisNode - Pointer to PlaylistNode object to be displayed */

void PrintPlaylistNode(PlaylistNode *thisNode)
{
    if (thisNode != NULL)
    {
        printf("Unique ID: %s\n", thisNode->uniqueID);
        printf("Song Name: %s\n", thisNode->songName);
        printf("Artist Name: %s\n", thisNode->artistName);
        printf("Song Length (in seconds): %d\n", thisNode->songLength);
    }
}

/* DestroyPlaylistNode: Release memory allocated by malloc in the
* CreatePlaylistNode function. Does nothing if thisNode is NULL
* thisNode - Pointer to PlaylistNode object to be freed.
*/

void DestroyPlaylistNode(PlaylistNode *thisNode)
{
    if (thisNode != NULL)
    {
        thisNode->nextNodePtr = NULL;
        free(thisNode);
        thisNode = NULL;
    }
}
