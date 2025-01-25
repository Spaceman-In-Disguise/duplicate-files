CC=gcc

main: main.c queue.c files.c queue.c hashmd5.c executemode.c librarymode.c libmd5.a
	$(CC) -g -o main main.c files.c queue.c hashmd5.c executemode.c librarymode.c libmd5.a