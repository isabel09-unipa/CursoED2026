// Header de viajes
// Declaraciones de funciones para manejar los viajes (arbol AVL)

#ifndef VIAJES_H
#define VIAJES_H

#include "estructuras.h"

// obtiene la altura de un nodo del arbol
int altura(viaje *nodo);

// calcula el balance del arbol en un nodo
int factorBalance(viaje *nodo);

// rotar el arbol hacia la derecha (para balancear)
viaje *rotarDerecha(viaje *y);

// rotar el arbol hacia la izquierda (para balancear)
viaje *rotarIzquierda(viaje *x);

// inserta un nuevo viaje en el arbol manteniendo el balance
viaje *insertarViaje(viaje *raiz, int codigo, int capacidad, int *insertado);

// busca un viaje en el arbol por su codigo
viaje *buscarViaje(viaje *raiz, int codigo);

// muestra el arbol de forma visual/ascii
void mostrarArbol(viaje *raiz, int nivel);

// cuenta cuantos viajes hay en el arbol
int contarViajes(viaje *raiz);

// suma todos los pasajeros embarcados en el arbol
int sumarEmbarcadosArbol(viaje *raiz);

// libera toda la memoria del arbol
void liberarArbol(viaje *raiz);

// opcion del menu para registrar un viaje
void registrarViajePrograma(void);

// opcion del menu para buscar un viaje
void buscarViajeMenu(void);

// opcion del menu para mostrar el arbol
void mostrarArbolMenu(void);

#endif // VIAJES_H
