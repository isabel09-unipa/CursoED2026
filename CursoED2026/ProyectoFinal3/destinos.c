#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destinos.h"
#include "pasajeros.h"
#include "viajes.h"
#include "utils.h"

destino *listaDestinos = NULL;

static void quitarNuevaLinea(char *texto) {
    if (texto == NULL) {
        return;
    }
    size_t longitud = strlen(texto);
    if (longitud > 0 && texto[longitud - 1] == '\n') {
        texto[longitud - 1] = '\0';
    }
}

destino *buscarDestino(int codigo) {
    destino *actual = listaDestinos;
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void registrarDestino(void) {
    int codigo;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigo) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se registro el destino.\n");
        return;
    }
    limpiarBuffer();

    if (buscarDestino(codigo) != NULL) {
        printf("El destino con codigo %d ya existe.\n", codigo);
        return;
    }

    destino *nuevo = malloc(sizeof(destino));
    if (nuevo == NULL) {
        printf("Error de memoria al registrar el destino.\n");
        return;
    }
    nuevo->codigo = codigo;
    printf("Ingrese el nombre del destino: ");
    if (fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin) == NULL) {
        free(nuevo);
        printf("Error al leer el nombre del destino.\n");
        return;
    }
    quitarNuevaLinea(nuevo->nombre);

    printf("Ingrese la empresa del destino: ");
    if (fgets(nuevo->empresa, sizeof(nuevo->empresa), stdin) == NULL) {
        free(nuevo);
        printf("Error al leer la empresa del destino.\n");
        return;
    }
    quitarNuevaLinea(nuevo->empresa);

    nuevo->colaPasajeros.frente = NULL;
    nuevo->colaPasajeros.final = NULL;
    nuevo->raizViajes = NULL;
    nuevo->siguiente = NULL;

    if (listaDestinos == NULL) {
        listaDestinos = nuevo;
    } else {
        destino *ultimo = listaDestinos;
        while (ultimo->siguiente != NULL) {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevo;
    }
    printf("Destino registrado correctamente.\n");
}

void mostrarDestinos(void) {
    if (listaDestinos == NULL) {
        printf("No hay destinos registrados.\n");
        return;
    }

    destino *actual = listaDestinos;
    while (actual != NULL) {
        int pasajerosEnEspera = contarPasajeros(actual);
        int viajesProgramados = contarViajes(actual->raizViajes);
        printf("Codigo: %d\n", actual->codigo);
        printf("Nombre: %s\n", actual->nombre);
        printf("Empresa: %s\n", actual->empresa);
        printf("Pasajeros en espera: %d\n", pasajerosEnEspera);
        printf("Viajes programados: %d\n", viajesProgramados);
        printf("-------------------------------\n");
        actual = actual->siguiente;
    }
}

void modificarDestino(void) {
    int codigo;
    printf("Ingrese el codigo del destino a modificar: ");
    if (scanf("%d", &codigo) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se modifico ningun destino.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigo);
    if (d == NULL) {
        printf("Destino con codigo %d no encontrado.\n", codigo);
        return;
    }

    printf("Ingrese el nuevo nombre del destino: ");
    if (fgets(d->nombre, sizeof(d->nombre), stdin) == NULL) {
        printf("Error al leer el nombre del destino.\n");
        return;
    }
    quitarNuevaLinea(d->nombre);

    printf("Ingrese la nueva empresa del destino: ");
    if (fgets(d->empresa, sizeof(d->empresa), stdin) == NULL) {
        printf("Error al leer la empresa del destino.\n");
        return;
    }
    quitarNuevaLinea(d->empresa);

    printf("Destino modificado correctamente.\n");
}

void liberarDestinos(void) {
    destino *actual = listaDestinos;
    while (actual != NULL) {
        destino *siguiente = actual->siguiente;
        liberarColaPasajeros(actual);
        liberarArbol(actual->raizViajes);
        free(actual);
        actual = siguiente;
    }
    listaDestinos = NULL;
}
