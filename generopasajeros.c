#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pasajeros.h"
#include "viajes.h"
#include "utils.h"
#include "genero.h"

int genero_pasajeros(Pasajero* pasajeros, int len, int* cantidadHombres, int* cantidadMujeres) {
    if (pasajeros == NULL || len <= 0 || cantidadHombres == NULL || cantidadMujeres == NULL) {
        return -1; // Error: parámetros inválidos
    }

    *cantidadHombres = 0;
    *cantidadMujeres = 0;

    for (int i = 0; i < len; i++) {
        if (pasajeros[i].isEmpty == 0) { // Verifica si el pasajero está activo
            if (pasajeros[i].genero == 'M') {
                (*cantidadHombres)++;
            } else if (pasajeros[i].genero == 'F') {
                (*cantidadMujeres)++;
            }
        }
    }

    return 0; // Éxito
}