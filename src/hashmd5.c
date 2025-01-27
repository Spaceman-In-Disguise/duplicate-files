#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"

char *getHash_lib(char *filename)
{
    return calculate_md5(filename);
}

char *getHash_exec(char *filename)
{
    create_pipe(pipe_fd);
    pid = create_fork();
    return validate(filename);
}

int compare_files(char *filenameA, char *filenameB, int mode)
{
    char *hashv1;
    char *hashv2;
    int result;
    if (mode == 0)
    {
        hashv1 = getHash_exec(filenameA);
        hashv2 = getHash_exec(filenameB);
    }
    if (mode == 1)
    {
        hashv1 = getHash_lib(filenameA);
        hashv2 = getHash_lib(filenameB);
    }
    if (strcmp(hashv1, hashv2) == 0)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    // printf("%s\n", hashv1);
    // printf("%s\n", hashv2);
    free(hashv1);
    free(hashv2);
    return result;
}
/*
int main(){
    char* file1 = "files.c";
    char* file2 = "queue.c";
    int result = compare_files(file1, file2, 0);
    printf("%d\n", result);
    return 0;
}
*/
