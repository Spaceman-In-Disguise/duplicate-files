#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

#include "hash.h"

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

int pipe_fd [2];
pid_t pid;


void create_pipe(int pipe_fd [2]) {
    if (pipe(pipe_fd ) == -1) {
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

void child_process(int pipe_fd [2], char *filename) {
    dup2(pipe_fd [1], STDOUT_FILENO);  // Redirect stdout to pipe
    close(pipe_fd [0]);
    close(pipe_fd [1]);
    execl("md5", "md5", filename, (char *)0);  // Execute md5
    die("execl");
}

void parent_process(int pipe_fd [2]) {
    char foo[4096];
    close(pipe_fd [1]);
    read(pipe_fd [0], foo, sizeof(foo));  // Read from pipe
    printf("%s", foo);
    close(pipe_fd [0]);
    wait(NULL);
}

// executes the code of the parent and the child
void validate (char *filename) {

    if (pid == 0) {
        child_process(pipe_fd, filename); 
    } else {
        parent_process(pipe_fd );
    }

}

/*int main() {


    create_pipe(pipe_fd );
    pid = create_fork();
    validate();

    return 0;
}*/