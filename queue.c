// Defining a QUEUE (FIFO) Data Structures to Save the Files Info.

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

File createFile(char* name, char* hashV, char* path) {
    struct File* newFile = (struct File*)malloc(sizeof(struct File));
    if (newFile == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newFile->name = strdup(name); // Allocate memory for name and copy
    newFile->hashV = strdup(hashV);     // Allocate memory for hashV and copy
    newFile->path = strdup(path); // Allocate memory for path and copy
    return *newFile;
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
    newNode->data = value; // Direct copy since members are fixed-size arrays
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
        printf("Error: Queue underflow.\n");
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
        dequeue(queue);
    }
}

void printQueue(Queue *queue){
    
    Node *currentNode = queue->front;
    File extractedFile;
    int i = 0;
    while (currentNode != NULL) {
        File extractedFile = currentNode->data;
        printf("File %d, Name: %s, Hash: %s, Path: %s\n", i, extractedFile.name, extractedFile.hashV, extractedFile.path);
        i++;
        currentNode = currentNode ->next;
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

    return 0;
}
*/
