// Funciones de utilidad
// Cosas que usamos en varios lados del programa

#include <stdio.h>
#include "utils.h"

// funcion para limpiar el buffer de entrada
// cuando scanf no consume toda la linea, esto borra lo que queda
void limpiarBuffer(void) {
    int c;
    // leo caracteres hasta encontrar un salto de linea o fin de archivo
    while ((c = getchar()) != '\n' && c != EOF) {
        // no hago nada, solo avanzo
    }
}
