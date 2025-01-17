CC=gcc

main: main.c queue.c files.c
	$(CC) -o main main.c queue.c files.c