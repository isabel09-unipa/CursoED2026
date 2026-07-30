// Header de pasajeros
// Declaraciones de funciones para manejar los pasajeros

#ifndef PASAJEROS_H
#define PASAJEROS_H

#include "destinos.h"

// contadores globales para las estadisticas
extern int totalRegistrados;    // cuantos pasajeros se registraron en total
extern int totalEmbarcados;     // cuantos ya se embarcaron

// busca un pasajero en todos los destinos por su documento
int buscarPasajeroGlobal(int documento, destino **destinoEncontrado);

// obtiene el primer pasajero en espera de un destino
pasajero *consultarPrimerPasajero(destino *d);

// verifica si la cola de un destino esta vacia
int colaVacia(destino *d);

// cuenta cuantos pasajeros en espera hay en un destino
int contarPasajeros(destino *d);

// registra un nuevo pasajero en un destino
void registrarPasajero(void);

// muestra todos los pasajeros de un destino
void mostrarPasajerosDestino(destino *d);

// opcion del menu para mostrar pasajeros
void mostrarPasajerosDestinoMenu(void);

// embarcar a un pasajero en un viaje
void embarcarPasajero(void);

// buscar en que destino y viaje esta un pasajero
void consultarUbicacionPasajero(void);

// libera la memoria de la cola de pasajeros
void liberarColaPasajeros(destino *d);

#endif // PASAJEROS_H
