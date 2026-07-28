#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pasajeros.h"
#include "viajes.h"
#include "utils.h"

int totalRegistrados = 0;
int totalEmbarcados = 0;

int buscarPasajeroGlobal(int documento, destino **destinoEncontrado) {
    destino *actualDestino = listaDestinos;
    while (actualDestino != NULL) {
        pasajero *actualPasajero = actualDestino->colaPasajeros.frente;
        while (actualPasajero != NULL) {
            if (actualPasajero->documento == documento) {
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

pasajero *consultarPrimerPasajero(destino *d) {
    if (d == NULL) {
        return NULL;
    }
    pasajero *actual = d->colaPasajeros.frente;
    while (actual != NULL) {
        if (strcmp(actual->estado, "en espera") == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

int colaVacia(destino *d) {
    return consultarPrimerPasajero(d) == NULL;
}

int contarPasajeros(destino *d) {
    if (d == NULL) {
        return 0;
    }
    int contador = 0;
    pasajero *actual = d->colaPasajeros.frente;
    while (actual != NULL) {
        if (strcmp(actual->estado, "en espera") == 0) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

void registrarPasajero(void) {
    int codigoDestino;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se registro el pasajero.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Destino con codigo %d no encontrado.\n", codigoDestino);
        return;
    }

    int documento;
    printf("Ingrese el documento del pasajero: ");
    if (scanf("%d", &documento) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se registro el pasajero.\n");
        return;
    }
    limpiarBuffer();

    destino *destinoEncontrado = NULL;
    if (buscarPasajeroGlobal(documento, &destinoEncontrado)) {
        printf("Ya existe un pasajero con documento %d.\n", documento);
        return;
    }

    int opcionTipo;
    printf("Seleccione el tipo de documento:\n");
    printf("1. Cedula de Ciudadania\n");
    printf("2. Pasaporte\n");
    printf("3. Tarjeta de Identidad\n");
    printf("Opcion: ");
    if (scanf("%d", &opcionTipo) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se registro el pasajero.\n");
        return;
    }
    limpiarBuffer();

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
            printf("Opcion de documento invalida. No se registro el pasajero.\n");
            return;
    }

    pasajero *nuevo = malloc(sizeof(pasajero));
    if (nuevo == NULL) {
        printf("Error de memoria al registrar el pasajero.\n");
        return;
    }

    nuevo->documento = documento;
    strcpy(nuevo->tipoDocumento, tipoDocumento);
    strcpy(nuevo->estado, "en espera");
    nuevo->viajeAsociado = 0;
    nuevo->siguiente = NULL;

    if (d->colaPasajeros.final == NULL) {
        d->colaPasajeros.frente = nuevo;
        d->colaPasajeros.final = nuevo;
    } else {
        d->colaPasajeros.final->siguiente = nuevo;
        d->colaPasajeros.final = nuevo;
    }

    totalRegistrados++;
    printf("Pasajero registrado en espera correctamente.\n");
}

void mostrarPasajerosDestino(destino *d) {
    if (d == NULL) {
        printf("Destino invalido.\n");
        return;
    }
    if (d->colaPasajeros.frente == NULL) {
        printf("No hay pasajeros registrados para el destino %d.\n", d->codigo);
        return;
    }

    pasajero *actual = d->colaPasajeros.frente;
    int indice = 1;
    while (actual != NULL) {
        printf("Pasajero %d:\n", indice);
        printf("  Documento: %d\n", actual->documento);
        printf("  Tipo de documento: %s\n", actual->tipoDocumento);
        printf("  Estado: %s\n", actual->estado);
        if (strcmp(actual->estado, "embarcado") == 0) {
            printf("  Viaje asociado: %d\n", actual->viajeAsociado);
        }
        printf("-------------------------------\n");
        actual = actual->siguiente;
        indice++;
    }
}

void mostrarPasajerosDestinoMenu(void) {
    int codigoDestino;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se puede mostrar la lista.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Destino con codigo %d no encontrado.\n", codigoDestino);
        return;
    }

    mostrarPasajerosDestino(d);
}

void embarcarPasajero(void) {
    int codigoDestino;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se pudo realizar el embarque.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Destino con codigo %d no encontrado.\n", codigoDestino);
        return;
    }

    int codigoViaje;
    printf("Ingrese el codigo del viaje: ");
    if (scanf("%d", &codigoViaje) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se pudo realizar el embarque.\n");
        return;
    }
    limpiarBuffer();

    viaje *v = buscarViaje(d->raizViajes, codigoViaje);
    if (v == NULL) {
        printf("Viaje con codigo %d no encontrado para el destino %d.\n", codigoViaje, codigoDestino);
        return;
    }
    if (v->pasajerosEmbarcados >= v->capacidad) {
        printf("El viaje %d ya esta lleno.\n", codigoViaje);
        return;
    }

    pasajero *primerPasajero = consultarPrimerPasajero(d);
    if (primerPasajero == NULL) {
        printf("No hay pasajeros en espera para el destino %d.\n", codigoDestino);
        return;
    }

    strcpy(primerPasajero->estado, "embarcado");
    primerPasajero->viajeAsociado = codigoViaje;
    v->pasajerosEmbarcados++;
    totalEmbarcados++;
    printf("Pasajero con documento %d embarcado en el viaje %d.\n", primerPasajero->documento, codigoViaje);
}

void consultarUbicacionPasajero(void) {
    int documento;
    printf("Ingrese el documento del pasajero: ");
    if (scanf("%d", &documento) != 1) {
        limpiarBuffer();
        printf("Entrada invalida.\n");
        return;
    }
    limpiarBuffer();

    destino *actualDestino = listaDestinos;
    while (actualDestino != NULL) {
        pasajero *actualPasajero = actualDestino->colaPasajeros.frente;
        while (actualPasajero != NULL) {
            if (actualPasajero->documento == documento) {
                if (strcmp(actualPasajero->estado, "en espera") == 0) {
                    printf("El pasajero con documento %d esta en espera en el destino %s (codigo %d).\n",
                           documento, actualDestino->nombre, actualDestino->codigo);
                } else {
                    printf("El pasajero con documento %d esta embarcado en el viaje %d del destino %s (codigo %d).\n",
                           documento, actualPasajero->viajeAsociado, actualDestino->nombre, actualDestino->codigo);
                }
                return;
            }
            actualPasajero = actualPasajero->siguiente;
        }
        actualDestino = actualDestino->siguiente;
    }
    printf("No se encontro un pasajero con documento %d.\n", documento);
}

void liberarColaPasajeros(destino *d) {
    if (d == NULL) {
        return;
    }
    pasajero *actual = d->colaPasajeros.frente;
    while (actual != NULL) {
        pasajero *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    d->colaPasajeros.frente = NULL;
    d->colaPasajeros.final = NULL;
}
