#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hash.h"

char filename[256];

// ask for the user file name
void get_filename(char *filename, size_t size) {
    printf("Ingrese el nombre del archivo: ");
    scanf("%255s", filename); // Leer el nombre del archivo desde la entrada estándar
}

// calculate and print the md5 hash
char* calculate_md5(char *filename) {
    char foo[33]; // Buffer para almacenar el valor hash
    int result = MDFile(filename, foo, sizeof(foo) - 1);

    if (result == 0) {
        printf("Error calculating MD5 hash\n");
    } else {
        //printf("Output: %s\n", hashValue);
        char* hashv = (char*)malloc(strlen(foo) + 1);
        strncpy(hashv, foo, 32);
        return hashv;
    }
}

/*int main() {
    char filename[256]; // Buffer para almacenar el nombre del archivo

    // Pedir el nombre del archivo al usuario
    get_filename(filename, sizeof(filename));

    // Calcular y mostrar el hash MD5
    calculate_and_print_md5(filename);

    return 0;
}*/