#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct File
{
    char* name;
    char* hashV;
    char* path;
} File;

typedef struct Node
{
    File data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;


extern File createFile();
extern void initializeQueue();
extern bool isQueueEmpty();
extern void enqueue();
extern File dequeue();
extern File peek();
extern void freeQueue();
extern void printQueue();
extern void freeFile();
#endif