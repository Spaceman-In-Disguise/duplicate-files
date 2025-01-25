#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"
#include "files.h"
#include "hash.h"
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

Queue filesView, folderView;
int readingFiles = 0;
pthread_mutex_t lockFolders;

//Variables in parameters
char *path = ".";
int nThreads = 100;
int appMode = 0;


// The first locks the acces to the top of the folder queue

void *lookFiles( )
{
    //Add files to folder
    while (!isQueueEmpty(&folderView) || readingFiles) // Repeat till no more folders to be found
    {
        if (!isQueueEmpty(&folderView)) // Not Empty
        {
            pthread_mutex_lock(&lockFolders);
            char *path = dequeue(&folderView).path;
            pthread_mutex_unlock(&lockFolders);
            if (path[0] == '\0')
            {
                break;
            } // Was an empty
            else
            {
                // printf("Thread %d\n and path %s\n .", id, path);
                readingFiles++;
                listFiles(path, &filesView, &folderView);
                readingFiles--;
            }
        }
        else if (readingFiles != 0) // Empty Queue but reading files
        {
            while (readingFiles != 0)
            {
                if (!isQueueEmpty(&folderView))
                {
                    break;
                }
            }
        }
    }
    return NULL;
}

int main(int argc, char* argv[])
{

    //Filter Arguments from command line
    path = argv[4];
    nThreads = atoi(argv[2]);
    if (argv[6][0]=='l')
    {
        appMode = 1;
    }
    
    initializeQueue(&filesView);
    initializeQueue(&folderView);
    enqueue(&folderView, createFile("", path, ""));

    pthread_mutex_init(&lockFolders, NULL);
    pthread_t agents[nThreads];
    for (int i = 0; i < nThreads; i++)
    {
        pthread_create(&agents[i], NULL, lookFiles, NULL );
    }
    for (int i = 0; i < nThreads; i++)
    {
        pthread_join(agents[i], NULL);
    }
 

    printQueue(&filesView);

    freeQueue(&filesView);
    freeQueue(&folderView);
    pthread_mutex_destroy(&lockFolders);
    return 0;
}
