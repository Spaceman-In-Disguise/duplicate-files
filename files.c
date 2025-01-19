#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"

char *pathcat(const char *str1, char *str2)
{
    // Calculate the total length of the resulting string
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t total_len = len1 + len2 + 1; // +1 for the '/' and null terminator

    // Allocate memory for the resulting string
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    // Concatenate the strings with '/' in between
    strcpy(result, str1);
    strcat(result, "/");
    strcat(result, str2);

    return result;
}

void listFiles(char *path, Queue *files_queue, Queue *folders_queue)
{
    
	char *fullpath;
	struct dirent *dp;
    
	DIR *dir = opendir(path); // Open the directory - dir contains a pointer to manage the dir
	int i = 0;
	while (dp = readdir(dir)) // if dp is null, there's no more content to read
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 ||strcmp(dp->d_name, "...") == 0){continue;}
		fullpath = pathcat(path, dp->d_name);
		if (dp -> d_type == DT_REG)
		{
        	enqueue(files_queue, createFile(dp->d_name, "", fullpath));
		}
		else if (dp -> d_type == DT_DIR)
		{
			enqueue(folders_queue, createFile(dp->d_name, "", fullpath));
		}
        
		free(fullpath);
		i++;
	}
	closedir(dir); // close the handle (pointer)
}

