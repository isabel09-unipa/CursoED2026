#ifndef VIAJES_H
#define VIAJES_H

#include "estructuras.h"

int altura(viaje *nodo);
int factorBalance(viaje *nodo);
viaje *rotarDerecha(viaje *y);
viaje *rotarIzquierda(viaje *x);
viaje *insertarViaje(viaje *raiz, int codigo, int capacidad, int *insertado);
viaje *buscarViaje(viaje *raiz, int codigo);
void mostrarArbol(viaje *raiz, int nivel);
int contarViajes(viaje *raiz);
int sumarEmbarcadosArbol(viaje *raiz);
void liberarArbol(viaje *raiz);
void registrarViajePrograma(void);
void buscarViajeMenu(void);
void mostrarArbolMenu(void);

#endif // VIAJES_H
