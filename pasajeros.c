// Manejo de pasajeros en el terminal
// Aqui registramos, buscamos y embarcamos a los pasajeros

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pasajeros.h"
#include "viajes.h"
#include "utils.h"

// contadores globales
int totalRegistrados = 0;  // cuantos pasajeros registramos en total
int totalEmbarcados = 0;   // cuantos de los registrados ya se embarcaron

// busca un pasajero en toda la base de datos por su documento
// devuelve 1 si lo encontro, 0 si no
int buscarPasajeroGlobal(int documento, destino **destinoEncontrado) {
    destino *actualDestino = listaDestinos;
    // recorro todos los destinos
    while (actualDestino != NULL) {
        pasajero *actualPasajero = actualDestino->colaPasajeros.frente;
        // por cada destino, recorro todos sus pasajeros
        while (actualPasajero != NULL) {
            if (actualPasajero->documento == documento) {
                // lo encontre! guardo en que destino estaba
                if (destinoEncontrado != NULL) {
                    *destinoEncontrado = actualDestino;
                }
                return 1;
            }
            actualPasajero = actualPasajero->siguiente;
        }
        actualDestino = actualDestino->siguiente;
    }
    if (destinoEncontrado != NULL) {
        *destinoEncontrado = NULL;
    }
    return 0;
}

// obtiene el primer pasajero de un destino que este en espera
pasajero *consultarPrimerPasajero(destino *d) {
    if (d == NULL) {
        return NULL;
    }
    pasajero *actual = d->colaPasajeros.frente;
    // recorro la cola hasta encontrar alguien en espera
    while (actual != NULL) {
        if (strcmp(actual->estado, "en espera") == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// verifica si la cola de pasajeros esta vacia (nadie en espera)
int colaVacia(destino *d) {
    return consultarPrimerPasajero(d) == NULL;
}

// cuenta cuantos pasajeros en espera hay en un destino
int contarPasajeros(destino *d) {
    if (d == NULL) {
        return 0;
    }
    int contador = 0;
    pasajero *actual = d->colaPasajeros.frente;
    while (actual != NULL) {
        if (strcmp(actual->estado, "en espera") == 0) {
            contador++; // cuento solo los que estan en espera
        }
        actual = actual->siguiente;
    }
    return contador;
}

// registra un pasajero nuevo en un destino
void registrarPasajero(void) {
    int codigoDestino;
    printf("Codigo del destino donde va el pasajero: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // busco el destino
    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Ese destino %d no existe!\n", codigoDestino);
        return;
    }

    // ahora pido el numero de documento del pasajero
    int documento;
    printf("Numero de documento del pasajero: ");
    if (scanf("%d", &documento) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // verifico que ese documento no ya exista en otro destino
    destino *destinoEncontrado = NULL;
    if (buscarPasajeroGlobal(documento, &destinoEncontrado)) {
        printf("Ya existe un pasajero con ese documento %d!\n", documento);
        return;
    }

    // ahora pido el tipo de documento
    int opcionTipo;
    printf("Que tipo de documento tiene?\n");
    printf("1. Cedula de Ciudadania\n");
    printf("2. Pasaporte\n");
    printf("3. Tarjeta de Identidad\n");
    printf("Elige: ");
    if (scanf("%d", &opcionTipo) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // convierto el numero en string
    char tipoDocumento[30];
    switch (opcionTipo) {
        case 1:
            strcpy(tipoDocumento, "Cedula de Ciudadania");
            break;
        case 2:
            strcpy(tipoDocumento, "Pasaporte");
            break;
        case 3:
            strcpy(tipoDocumento, "Tarjeta de Identidad");
            break;
        default:
            printf("Esa opcion no existe!\n");
            return;
    }

    // creo un nuevo pasajero
    pasajero *nuevo = malloc(sizeof(pasajero));
    if (nuevo == NULL) {
        printf("Problema de memoria! No se pudo registrar.\n");
        return;
    }

    // guardo los datos
    nuevo->documento = documento;
    strcpy(nuevo->tipoDocumento, tipoDocumento);
    strcpy(nuevo->estado, "en espera");
    nuevo->viajeAsociado = 0;
    nuevo->siguiente = NULL;

    // lo agrego a la cola del destino
    if (d->colaPasajeros.final == NULL) {
        // si la cola esta vacia, es el primero
        d->colaPasajeros.frente = nuevo;
        d->colaPasajeros.final = nuevo;
    } else {
        // sino, lo agrego al final
        d->colaPasajeros.final->siguiente = nuevo;
        d->colaPasajeros.final = nuevo;
    }

    totalRegistrados++;
    printf("Pasajero registrado correctamente! Esta en espera.\n");
}

// muestra todos los pasajeros de un destino
void mostrarPasajerosDestino(destino *d) {
    if (d == NULL) {
        printf("Ese destino no existe.\n");
        return;
    }
    if (d->colaPasajeros.frente == NULL) {
        printf("No hay pasajeros en el destino %d.\n", d->codigo);
        return;
    }

    // recorro la lista de pasajeros
    pasajero *actual = d->colaPasajeros.frente;
    int indice = 1;
    while (actual != NULL) {
        printf("Pasajero numero %d:\n", indice);
        printf("  Documento: %d\n", actual->documento);
        printf("  Tipo: %s\n", actual->tipoDocumento);
        printf("  Estado: %s\n", actual->estado);
        if (strcmp(actual->estado, "embarcado") == 0) {
            printf("  Viaje en el que viaja: %d\n", actual->viajeAsociado);
        }
        printf("-------------------------------\n");
        actual = actual->siguiente;
        indice++;
    }
}

// opcion del menu para mostrar pasajeros
void mostrarPasajerosDestinoMenu(void) {
    int codigoDestino;
    printf("Codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Ese destino %d no existe!\n", codigoDestino);
        return;
    }

    mostrarPasajerosDestino(d);
}

// funcion para embarcar a un pasajero en un viaje
void embarcarPasajero(void) {
    int codigoDestino;
    printf("Codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Ese destino %d no existe!\n", codigoDestino);
        return;
    }

    // ahora pido el viaje
    int codigoViaje;
    printf("Codigo del viaje: ");
    if (scanf("%d", &codigoViaje) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // busco el viaje en el arbol de viajes del destino
    viaje *v = buscarViaje(d->raizViajes, codigoViaje);
    if (v == NULL) {
        printf("Ese viaje %d no existe en el destino!\n", codigoViaje);
        return;
    }
    
    // verifico que el viaje no este lleno
    if (v->pasajerosEmbarcados >= v->capacidad) {
        printf("El viaje %d esta completo! No caben mas pasajeros.\n", codigoViaje);
        return;
    }

    // obtengo el primer pasajero en espera
    pasajero *primerPasajero = consultarPrimerPasajero(d);
    if (primerPasajero == NULL) {
        printf("No hay nadie esperando en ese destino.\n");
        return;
    }

    // lo embarco
    strcpy(primerPasajero->estado, "embarcado");
    primerPasajero->viajeAsociado = codigoViaje;
    v->pasajerosEmbarcados++;
    totalEmbarcados++;
    printf("Pasajero con documento %d embarcado en viaje %d!\n", primerPasajero->documento, codigoViaje);
}

// busca un pasajero por su documento en todo el sistema
void consultarUbicacionPasajero(void) {
    int documento;
    printf("Numero de documento del pasajero: ");
    if (scanf("%d", &documento) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // recorro todos los destinos buscando el pasajero
    destino *actualDestino = listaDestinos;
    while (actualDestino != NULL) {
        pasajero *actualPasajero = actualDestino->colaPasajeros.frente;
        while (actualPasajero != NULL) {
            if (actualPasajero->documento == documento) {
                // lo encontre! muestro donde esta
                if (strcmp(actualPasajero->estado, "en espera") == 0) {
                    printf("Pasajero %d esta esperando en %s (destino %d).\n",
                           documento, actualDestino->nombre, actualDestino->codigo);
                } else {
                    printf("Pasajero %d ya esta embarcado en viaje %d del destino %s (codigo %d).\n",
                           documento, actualPasajero->viajeAsociado, actualDestino->nombre, actualDestino->codigo);
                }
                return;
            }
            actualPasajero = actualPasajero->siguiente;
        }
        actualDestino = actualDestino->siguiente;
    }
    printf("No encontre un pasajero con ese documento %d.\n", documento);
}

// libera la memoria de la cola de pasajeros de un destino
void liberarColaPasajeros(destino *d) {
    if (d == NULL) {
        return;
    }
    pasajero *actual = d->colaPasajeros.frente;
    while (actual != NULL) {
        pasajero *siguiente = actual->siguiente;
        free(actual); // libero cada pasajero
        actual = siguiente;
    }
    d->colaPasajeros.frente = NULL;
    d->colaPasajeros.final = NULL;
}
