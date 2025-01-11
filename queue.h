#ifndef QUEUE_H
#define QUEUE_H
//#include <stdbool.h>

typedef struct {
    char name[128];
    char hashV[33];
    char path[128];
} File;

typedef struct Node {
    File data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;


extern void hello();
extern void initializeQueue();
//extern bool isQueueEmpty();
extern void enqueue();
struct File dequeue();
struct File peek();
extern void freeQueue();


#endif