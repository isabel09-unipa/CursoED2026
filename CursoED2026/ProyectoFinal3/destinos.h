#ifndef DESTINOS_H
#define DESTINOS_H

#include "estructuras.h"

extern destino *listaDestinos;

destino *buscarDestino(int codigo);
void registrarDestino(void);
void mostrarDestinos(void);
void modificarDestino(void);
void liberarDestinos(void);

#endif // DESTINOS_H
