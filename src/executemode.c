#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>

#include "hash.h"

#define die(e)                      \
    do                              \
    {                               \
        fprintf(stderr, "%s\n", e); \
        exit(EXIT_FAILURE);         \
    } while (0);

int pipe_fd[2];
pid_t pid;

void create_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1)
    {
        die("pipe");
    }
}

pid_t create_fork()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        die("fork");
    }
    return pid;
}

void child_process(int pipe_fd[2], char *filename)
{
    dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
    // Cierra el extremo de lectura
    close(pipe_fd[0]);
    // Cierra el extremo de escritura del Pipe ya duplicado

    // ESTO NO VA A FUNCIONA SI SACAS EL EJECUTABLE DEL AREA DE TRABAJO
    // investiga sobre los array de bytes y los arhivos temporales para incrutar ejecutables
    close(pipe_fd[1]);
    execl("mode/md5-app/md5", "mode/md5-app/md5", filename, (char *)0); // Execute md5
    die("execl");
}

char *parent_process(int pipe_fd[2])
{
    char foo[33];
    close(pipe_fd[1]);
    read(pipe_fd[0], foo, sizeof(foo)); // Read from pipe
    // printf("%s", foo);
    close(pipe_fd[0]);
    wait(NULL);
    char *hashv = (char *)malloc(strlen(foo) + 1);
    strncpy(hashv, foo, 32);
    return hashv;
}

// executes the code of the parent and the child
char *validate(char *filename)
{

    if (pid == 0)
    {
        child_process(pipe_fd, filename);
    }
    else
    {
        return parent_process(pipe_fd);
    }
}

/*int main() {


    create_pipe(pipe_fd );
    pid = create_fork();
    validate();

    return 0;
}*/