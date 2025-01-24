// Defining a QUEUE (FIFO) Data Structures to Save the Files Info.

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

File createFile(const char *name, const char *hash, const char *path)
{
    File newFile;
    newFile.name = malloc(strlen(name) + 1);
    newFile.hashV = malloc(strlen(hash) + 1);
    newFile.path = malloc(strlen(path) + 1);

    if (newFile.name == NULL || newFile.hashV == NULL || newFile.path == NULL) {
        // Handle allocation failure
        free(newFile.name);
        free(newFile.hashV);
        free(newFile.path);
        return (File){"", "", ""}; // Return an error value
    }

    strcpy(newFile.name, name);
    strcpy(newFile.hashV, hash);
    strcpy(newFile.path, path);

    return newFile;
}

void initializeQueue(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

bool isQueueEmpty(Queue *queue)
{
    return queue->front == NULL;
}

void enqueue(Queue *queue, File value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error: Could not allocate memory for node.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isQueueEmpty(queue))
    {
        queue->front = newNode;
    }
    else
    {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
}

File dequeue(Queue *queue)
{
    File errorValue = {"", "", ""}; // Error value, all members are empty strings
    if (isQueueEmpty(queue))
    {
        //printf("Error: Queue underflow.\n");
        return errorValue;
    }

    Node *nodeToRemove = queue->front;
    File value = nodeToRemove->data;

    queue->front = nodeToRemove->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(nodeToRemove);
    return value;
}

File peek(Queue *queue)
{
    File errorValue = {"", "", ""}; // Error value, all members are empty strings
    if (isQueueEmpty(queue))
    {
        printf("Error: Queue is empty.\n");
        return errorValue;
    }
    return queue->front->data;
}

void freeQueue(Queue *queue)
{
    while (!isQueueEmpty(queue))
    {
        File file = dequeue(queue);
        freeFile(&file); // Free the file data
    }
}

void printQueue(Queue *queue){
    
    Node *currentNode = queue->front;
    File extractedFile;
    int i = 0;
    while (currentNode != NULL) { // Repeat till end of queue is reached
        File extractedFile = currentNode->data;
        printf("File %d, Name: %s, Hash: %s, Path: %s\n", i, extractedFile.name, extractedFile.hashV, extractedFile.path);
        i++;
        currentNode = currentNode ->next;
    }
}

void freeFile(File* file) {
    if (file != NULL) {
        if (file->name != NULL) {
            free(file->name);
            file->name = NULL;
        }
        if (file->hashV != NULL) {
            free(file->hashV);
            file->hashV = NULL;
        }
        if (file->path != NULL) {
            free(file->path);
            file->path = NULL;
        }
    }
}

/* USED TO TEST THE MODULE
int main() {
    Queue myQueue;
    initializeQueue(&myQueue);

    enqueue(&myQueue, createFile("document.txt", "hash123456789012345678901234567", "/path/to/document.txt"));
    enqueue(&myQueue, createFile("image.jpg", "hash98765432109876543210987654321", "/path/to/image.jpg"));
    enqueue(&myQueue, createFile("program.exe", "hash45678901234567890123456789012", "/path/to/program.exe"));


   printQueue(&myQueue);

   freeQueue(&myQueue);

    return 0;
}

*/