#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main (){

    char letter;
    //para el modo libreria 
    printf ("escriba 'e' para el modo ejecutable y 'l' para el modo libreria \n");
    scanf ("%c", &letter );
    
    if (letter == 'l'){

    // Pedir el nombre del archivo al usuario
    get_filename(filename, sizeof(filename));

    // Calcular y mostrar el hash MD5
    calculate_and_print_md5(filename);
    }
    if (letter == 'e') {

    get_filename(filename, sizeof(filename));

    create_pipe(pipe_fd );
    pid = create_fork();
    validate(filename);

    }
}



