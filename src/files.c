#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"
#include "hash.h"

char *pathcat(const char *str1, char *str2)
{
	// Calculate the total length of the resulting string
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t total_len = len1 + len2 + 2; // +1 for the '/' and null terminator

	// Allocate memory for the resulting string
	char *result = (char *)malloc(total_len);
	if (result == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		return NULL;
	}

	// Concatenate the strings with '/' in between
	strcpy(result, str1);
	strcat(result, "/");
	strcat(result, str2);

	return result;
}

// Check if the directory name is special (e.g. "." or "..")
int isSpecialDirectory(const char *name)
{
	return (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || strcmp(name, "...") == 0);
}

// List all files in the given directory
void listFiles(char *path, Queue *files_queue, Queue *folders_queue)
{
	char *fullpath;
	struct dirent *dp;

	DIR *dir = opendir(path); // Open the directory - dir contains a pointer to manage the dir
	if (dir == NULL)
	{
		fprintf(stderr, "Could not open directory: %s\n", path);
		return;
	}
	int i = 0;
	while ((dp = readdir(dir)) != NULL) // if dp is null, there's no more content to read
	{
		if (isSpecialDirectory(dp->d_name))
		{
			continue;
		}
		fullpath = pathcat(path, dp->d_name);
		// CAMBIA ESTO XD. Es que me arroja que los identificadores no estan definidos y se ve feito
		if (dp->d_type == DT_REG)
		{
			enqueue(files_queue, createFile(dp->d_name, fullpath));
		}
		else if (dp->d_type == DT_DIR)
		{
			enqueue(folders_queue, createFile(dp->d_name, fullpath));
		}

		free(fullpath);
		i++;
	}
	closedir(dir); // close the handle (pointer)
}
