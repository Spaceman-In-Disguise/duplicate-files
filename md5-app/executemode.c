#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

//#include "hash.h"

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

void create_pipe(int link[2]) {
    if (pipe(link) == -1) {
        die("pipe");
    }
}

pid_t create_fork() {
    pid_t pid = fork();
    if (pid == -1) {
        die("fork");
    }
    return pid;
}

void child_process(int link[2]) {
    dup2(link[1], STDOUT_FILENO);
    close(link[0]);
    close(link[1]);
    execl("md5", "md5", "ej3.c", (char *)0);
    die("execl");
}

void parent_process(int link[2]) {
    char foo[4096];
    close(link[1]);
    read(link[0], foo, sizeof(foo));
    printf("%s", foo);
    close(link[0]);
    wait(NULL);
}

int main() {
    int link[2];
    pid_t pid;

    create_pipe(link);
    pid = create_fork();

    if (pid == 0) {
        child_process(link);
    } else {
        parent_process(link);
    }

    return 0;
}