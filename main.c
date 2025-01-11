#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "queue.h"
#include "queue.c" //ESTO HAY QUE QUITARLO

char *path = "C:\\Users\\usuario\\Documents\\UCV\\test"; // Directory target

char *pathcat(const char *str1, char *str2);

void listFiles(char *path)
{

	char *fullpath;
	struct dirent *dp;
	DIR *dir = opendir(path); // Open the directory - dir contains a pointer to manage the dir
	int i = 0;
	while (dp = readdir(dir)) // if dp is null, there's no more content to read
	{
		if(dp->d_name == "." || dp->d_name == ".."){continue;}
		fullpath = pathcat(path, dp->d_name);
		printf("File %d : %s\n", i, dp->d_name);
		free(fullpath);
		i++;
	}
	closedir(dir); // close the handle (pointer)
}

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

int main()
{	
	listFiles(path);
	return 0;
}