#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

char filename[256];

// ask for the user file name
void get_filename(char *filename, size_t size) {
    printf("Ingrese el nombre del archivo: ");
    scanf("%255s", filename); // Leer el nombre del archivo desde la entrada estándar
}

// calculate and print the md5 hash
void calculate_and_print_md5(const char *filename) {
    char hashValue[33]; // Buffer para almacenar el valor hash
    int result = MDFile(filename, hashValue, sizeof(hashValue) - 1);

    if (result == 0) {
        printf("Error calculating MD5 hash\n");
    } else {
        printf("Output: %s\n", hashValue);
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