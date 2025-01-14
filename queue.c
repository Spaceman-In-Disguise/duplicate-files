// Defining a QUEUE (FIFO) Data Structures to Save the Files Info.

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

/* USED TO TEST THE MODULE
int main() {
    Queue myQueue;
    initializeQueue(&myQueue);

    File file1 = {"document.txt", "hash123456789012345678901234567", "/path/to/document.txt"};
    File file2 = {"image.jpg", "hash98765432109876543210987654321", "/path/to/image.jpg"};
    File file3 = {"program.exe", "hash45678901234567890123456789012", "/path/to/program.exe"};

    enqueue(&myQueue, file1);
    enqueue(&myQueue, file2);
    enqueue(&myQueue, file3);

    File extractedFile;
    while (!isQueueEmpty(&myQueue)) {
        extractedFile = dequeue(&myQueue);
        if (strcmp(extractedFile.name, "") != 0) { // Check if not error value
            printf("Extracted file: Name: %s, Hash: %s, Path: %s\n", extractedFile.name, extractedFile.hashV, extractedFile.path);
        }
    }

    return 0;
}
*/