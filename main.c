#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"
#include "files.h"

int main()
{	
    Queue filesView;
    initializeQueue(&filesView);
    char *path = "."; // Directory target
	listFiles(path, &filesView);
    printQueue(&filesView);
    
	return 0;
}
