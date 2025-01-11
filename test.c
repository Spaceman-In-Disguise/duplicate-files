#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definition of the File struct
typedef struct {
    char name[50];
    int size;
    // Other members of the File struct...
} File;

// Definition of the queue node
typedef struct Node {
    File data;
    struct Node *next;
} Node;

// Definition of the queue
typedef struct {
    Node *front; // Pointer to the first element (front)
    Node *rear;  // Pointer to the last element (rear)
} Queue;

// Initializes the queue
void initializeQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Checks if the queue is empty
bool isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

// Enqueues an element
void enqueue(Queue *queue, File value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Could not allocate memory for the node.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL; // The new node is the last

    if (isQueueEmpty(queue)) {
        queue->front = newNode; // If the queue is empty, the new node is both front and rear
    } else {
        queue->rear->next = newNode; // Links the current last node to the new node
    }
    queue->rear = newNode; // The new node becomes the new rear
}

// Dequeues an element
File dequeue(Queue *queue) {
    File errorValue = {"", -1}; // Error value
    if (isQueueEmpty(queue)) {
        printf("Error: Queue underflow. Cannot extract.\n");
        return errorValue;
    }

    Node *nodeToRemove = queue->front;
    File value = nodeToRemove->data;

    queue->front = nodeToRemove->next; // Moves the front to the next node

    if (queue->front == NULL) { // If the last element was dequeued, the rear must also be NULL
        queue->rear = NULL;
    }

    free(nodeToRemove);
    return value;
}

// Gets the element at the front of the queue without removing it
File peek(Queue *queue) {
    File errorValue = {"", -1}; // Error value
    if (isQueueEmpty(queue)) {
        printf("Error: Queue is empty. No element at the front.\n");
        return errorValue;
    }
    return queue->front->data;
}

// Frees the memory occupied by the queue
void freeQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
}

int main() {
    Queue myQueue;
    initializeQueue(&myQueue);

    File file1 = {"document.txt", 1024};
    File file2 = {"image.jpg", 2048};
    File file3 = {"program.exe", 4096};

    enqueue(&myQueue, file1);
    enqueue(&myQueue, file2);
    enqueue(&myQueue, file3);

    File extractedFile = dequeue(&myQueue);
    if (strcmp(extractedFile.name, "") != 0)
        printf("Extracted file (dequeue): %s (Size: %d)\n", extractedFile.name, extractedFile.size);

    File frontFile = peek(&myQueue);
    if (strcmp(frontFile.name, "") != 0)
        printf("File at the front (peek): %s (Size: %d)\n", frontFile.name, frontFile.size);

    extractedFile = dequeue(&myQueue);
    if (strcmp(extractedFile.name, "") != 0)
        printf("Extracted file (dequeue): %s (Size: %d)\n", extractedFile.name, extractedFile.size);

    extractedFile = dequeue(&myQueue);
    if (strcmp(extractedFile.name, "") != 0)
        printf("Extracted file (dequeue): %s (Size: %d)\n", extractedFile.name, extractedFile.size);

    freeQueue(&myQueue);

    return 0;
}