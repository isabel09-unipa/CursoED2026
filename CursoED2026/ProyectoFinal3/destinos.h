// Header de destinos
// Declaraciones de funciones para manejar los destinos

#ifndef DESTINOS_H
#define DESTINOS_H

#include "estructuras.h"

// variable global que apunta al primer destino de la lista
extern destino *listaDestinos;

// funcion para buscar un destino por codigo
destino *buscarDestino(int codigo);

// funcion para registrar un nuevo destino
void registrarDestino(void);

// muestra todos los destinos registrados
void mostrarDestinos(void);

// cambia los datos de un destino existente
void modificarDestino(void);

// libera la memoria de todos los destinos al salir
void liberarDestinos(void);

#endif // DESTINOS_H
