#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"
#include "files.h"
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

Queue filesView, folderView;
int readingFiles = 0;
int nThreads = 100;
pthread_mutex_t lockFolders;
// The first locks the acces to the top of the folder queue

void *lookFiles( )
{

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
    // TERMINO TODO FIN DE LA FUNCIÓN
    return NULL;
}

int main()
{
    initializeQueue(&filesView);
    initializeQueue(&folderView);
    char *path = "/mnt/c/users/pvmir/documents/Doc-Mari/SO/proy1/duplicate-files/test";
    enqueue(&folderView, createFile("", "", path));

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

    return 0;
}
