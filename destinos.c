// Manejo de destinos del terminal portuario
// Aqui se crean, buscan y eliminan los destinos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destinos.h"
#include "pasajeros.h"
#include "viajes.h"
#include "utils.h"

// lista global de destinos, apuntador al primero
destino *listaDestinos = NULL;

// funcion para quitar el salto de linea al final de un string
// (porque fgets deja un \n)
static void quitarNuevaLinea(char *texto) {
    if (texto == NULL) {
        return;
    }
    // busco la longitud del string
    size_t longitud = strlen(texto);
    // si el ultimo caracter es \n, lo cambio por \0
    if (longitud > 0 && texto[longitud - 1] == '\n') {
        texto[longitud - 1] = '\0';
    }
}

// funcion para buscar un destino por su codigo
// recorre la lista y lo encuentra si existe
destino *buscarDestino(int codigo) {
    destino *actual = listaDestinos;
    // mientras no llegue al final
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return actual; // lo encontre!
        }
        actual = actual->siguiente;
    }
    return NULL; // no lo encontre
}

// funcion para agregar un destino nuevo
void registrarDestino(void) {
    int codigo;
    printf("Dame el codigo del destino (un numero): ");
    if (scanf("%d", &codigo) != 1) {
        limpiarBuffer();
        printf("Error! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // verifico que no exista otro destino con ese codigo
    if (buscarDestino(codigo) != NULL) {
        printf("Ya existe un destino con codigo %d, no se puede agregar otro igual!\n", codigo);
        return;
    }

    // creo el nuevo destino con malloc
    destino *nuevo = malloc(sizeof(destino));
    if (nuevo == NULL) {
        printf("No hay memoria disponible! Algo malo paso...\n");
        return;
    }
    
    // guardo el codigo
    nuevo->codigo = codigo;
    
    // ahora pido el nombre
    printf("Nombre del destino: ");
    if (fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin) == NULL) {
        free(nuevo);
        printf("Error al leer el nombre.\n");
        return;
    }
    quitarNuevaLinea(nuevo->nombre);

    // y pido la empresa
    printf("Empresa que maneja este destino: ");
    if (fgets(nuevo->empresa, sizeof(nuevo->empresa), stdin) == NULL) {
        free(nuevo);
        printf("Error al leer la empresa.\n");
        return;
    }
    quitarNuevaLinea(nuevo->empresa);

    // inicializo los campos de la cola de pasajeros y el arbol de viajes
    nuevo->colaPasajeros.frente = NULL;
    nuevo->colaPasajeros.final = NULL;
    nuevo->raizViajes = NULL;
    nuevo->siguiente = NULL;

    // si la lista esta vacia, este es el primero
    if (listaDestinos == NULL) {
        listaDestinos = nuevo;
    } else {
        // sino, busco el ultimo y lo agrego al final
        destino *ultimo = listaDestinos;
        while (ultimo->siguiente != NULL) {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevo;
    }
    printf("Destino guardado correctamente!\n");
}

// funcion para mostrar todos los destinos
void mostrarDestinos(void) {
    if (listaDestinos == NULL) {
        printf("No hay destinos en el sistema todavia.\n");
        return;
    }

    // recorro la lista y muestro cada uno
    destino *actual = listaDestinos;
    while (actual != NULL) {
        // cuento cuantos pasajeros hay en espera
        int pasajerosEnEspera = contarPasajeros(actual);
        // cuento cuantos viajes hay para este destino
        int viajesProgramados = contarViajes(actual->raizViajes);
        
        printf("--- DESTINO ---\n");
        printf("Codigo: %d\n", actual->codigo);
        printf("Nombre: %s\n", actual->nombre);
        printf("Empresa: %s\n", actual->empresa);
        printf("Pasajeros esperando: %d\n", pasajerosEnEspera);
        printf("Viajes programados: %d\n", viajesProgramados);
        printf("-------------------------------\n");
        actual = actual->siguiente;
    }
}

// funcion para modificar un destino existente
void modificarDestino(void) {
    int codigo;
    printf("Que codigo del destino quieres modificar? ");
    if (scanf("%d", &codigo) != 1) {
        limpiarBuffer();
        printf("Error! Escribe un numero.\n");
        return;
    }
    limpiarBuffer();

    // busco el destino
    destino *d = buscarDestino(codigo);
    if (d == NULL) {
        printf("No encontre ese destino con codigo %d.\n", codigo);
        return;
    }

    // pido el nuevo nombre
    printf("Nuevo nombre del destino: ");
    if (fgets(d->nombre, sizeof(d->nombre), stdin) == NULL) {
        printf("Error al leer.\n");
        return;
    }
    quitarNuevaLinea(d->nombre);

    // pido la nueva empresa
    printf("Nueva empresa: ");
    if (fgets(d->empresa, sizeof(d->empresa), stdin) == NULL) {
        printf("Error al leer.\n");
        return;
    }
    quitarNuevaLinea(d->empresa);

    printf("Destino modificado correctamente!\n");
}

// funcion para liberar toda la memoria de los destinos
// (esto se hace cuando el programa termina)
void liberarDestinos(void) {
    destino *actual = listaDestinos;
    while (actual != NULL) {
        destino *siguiente = actual->siguiente; // guardo el siguiente antes de borrar
        liberarColaPasajeros(actual); // libero los pasajeros
        liberarArbol(actual->raizViajes); // libero el arbol de viajes
        free(actual); // libero el destino
        actual = siguiente;
    }
    listaDestinos = NULL;
}
