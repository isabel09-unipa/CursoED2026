#ifndef PASAJEROS_H
#define PASAJEROS_H

#include "destinos.h"

extern int totalRegistrados;
extern int totalEmbarcados;

int buscarPasajeroGlobal(int documento, destino **destinoEncontrado);
pasajero *consultarPrimerPasajero(destino *d);
int colaVacia(destino *d);
int contarPasajeros(destino *d);
void registrarPasajero(void);
void mostrarPasajerosDestino(destino *d);
void mostrarPasajerosDestinoMenu(void);
void embarcarPasajero(void);
void consultarUbicacionPasajero(void);
void liberarColaPasajeros(destino *d);

#endif // PASAJEROS_H
