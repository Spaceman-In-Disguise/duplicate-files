#ifndef HASH_H
#define HASH_H

//execute mode
extern int pipe_fd [2];
extern pid_t pid;

//modo libreria
extern char filename[256];
extern int MDFile ();
extern void get_filename();
extern void calculate_and_print_md5();

//modo ejecucion
extern void create_pipe();
extern pid_t create_fork();
extern void child_process();
extern void parent_process();
extern void validate();

#endif