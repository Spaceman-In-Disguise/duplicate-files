#include <sys/types.h>
#ifndef HASH_H
#define HASH_H

// LIBRARY MDOE
extern MDFile();
extern char *calculate_md5();

// EXECUTE MODE
extern int pipe_fd[2];
extern pid_t pid;

extern void create_pipe();
extern pid_t create_fork();
extern char *validate();

// MAIN HASH COMPARATOR
extern int compare_files();
extern char *getHash_lib();
extern char *getHash_exec();
#endif