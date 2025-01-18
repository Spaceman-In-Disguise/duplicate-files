#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"

char *pathcat(const char *str1, char *str2)
{
	char *res;
	size_t strlen1 = strlen(str1);
	size_t strlen2 = strlen(str2);
	int i, j;
	res = malloc((strlen1 + strlen2 + 1) * sizeof *res);
	strcpy(res, str1);
	for (i = strlen1, j = 0; ((i < (strlen1 + strlen2)) && (j < strlen2)); i++, j++)
		res[i] = str2[j];
	res[strlen1 + strlen2] = '\0';
	return res;
}

void listFiles(char *path, Queue *files_queue)
{
    
	char *fullpath;
	struct dirent *dp;
    
	DIR *dir = opendir(path); // Open the directory - dir contains a pointer to manage the dir
	int i = 0;
	while (dp = readdir(dir)) // if dp is null, there's no more content to read
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 ||strcmp(dp->d_name, "...") == 0){continue;}
		fullpath = pathcat(path, dp->d_name);
        char *hashV = "hash45678901234567890123456789012";
        enqueue(files_queue, createFile(dp->d_name, hashV, fullpath));
        
		free(fullpath);
		i++;
	}
	closedir(dir); // close the handle (pointer)
}

