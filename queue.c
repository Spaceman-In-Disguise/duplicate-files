// Defining a QUEUE (FIFO) Data Structures to Save the Files Info.

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Create a new file with the given name, hash, and path
File createFile(const char *name, const char *path)
{
    File newFile;
    newFile.name = malloc(strlen(name) + 1);
    newFile.path = malloc(strlen(path) + 1);

    if (newFile.name == NULL || newFile.path == NULL) {
        // Handle allocation failure
        free(newFile.name);
        free(newFile.path);
        return (File){"", ""}; // Return an error value
    }

    strcpy(newFile.name, name);
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

// Add a new file to the end of the queue
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

// Remove and return the file at the front of the queue
File dequeue(Queue *queue)
{
    File errorValue = {"", ""}; // Error value, all members are empty strings
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

// Return the file at the front of the queue without removing it
File peek(Queue *queue)
{
    File errorValue = {"", ""}; // Error value, all members are empty strings
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
        File file = dequeue(queue); // Remove the file from the queue
        freeFile(&file); // Free the file data
    }
}

void printQueue(Queue *queue){
    
    Node *currentNode = queue->front;
    File extractedFile;
    int i = 0;
    while (currentNode != NULL) { // Repeat till end of queue is reached
        File extractedFile = currentNode->data;
        printf("File %d, Name: %s, Path: %s\n", i, extractedFile.name, extractedFile.path);
        i++;
        currentNode = currentNode ->next;
    }
}

// Free the memory allocated for the file data
void freeFile(File* file) {
    if (file != NULL) {
        if (file->name != NULL) {
            free(file->name);
            file->name = NULL;
        }
        if (file->path != NULL) {
            free(file->path);
            file->path = NULL;
        }
    }
}

/*USED TO TEST THE MODULE
int main() {
    Queue myQueue;
    initializeQueue(&myQueue);

    enqueue(&myQueue, createFile("document.txt", "/path/to/document.txt"));
    enqueue(&myQueue, createFile("image.jpg", "/path/to/image.jpg"));
    enqueue(&myQueue, createFile("program.exe", "/path/to/program.exe"));


   printQueue(&myQueue);

   freeQueue(&myQueue);

    return 0;
}

*/