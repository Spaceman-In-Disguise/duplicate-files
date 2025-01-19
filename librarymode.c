#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

// Prototipo de la función MDFile
//int MDFile(const char *filename, char *hash, size_t hash_len);
char filename[256];

// Función para pedir el nombre del archivo al usuario
void get_filename(char *filename, size_t size) {
    printf("Ingrese el nombre del archivo: ");
    scanf("%255s", filename); // Leer el nombre del archivo desde la entrada estándar
}

// Función para calcular y mostrar el hash MD5
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