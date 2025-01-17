#include <stdio.h>
#include <stdlib.h>
//#include "global.h"

// función MDFile
int MDFile(const char *filename, char *hash, size_t hash_len); 



int main (){

    char hashValue[33]; // Buffer para almacenar el valor hash
    int result = MDFile("ej3.c", hashValue, sizeof(hashValue) - 1);

    if (result == 0) {
        printf("Error calculating MD5 hash\n");

    } else {
        printf("Output: (%s)\n", hashValue);
    }    

    return 0;
}