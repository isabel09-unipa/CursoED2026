// Manejo de viajes usando un arbol AVL
// Los viajes se guardan en un arbol por cada destino

#include <stdio.h>
#include <stdlib.h>
#include "viajes.h"
#include "destinos.h"
#include "utils.h"

// funcion para obtener la altura de un nodo
// si el nodo es NULL, devuelve 0, sino devuelve su altura
int altura(viaje *nodo) {
    return nodo == NULL ? 0 : nodo->altura;
}

// calcula el factor de balance (diferencia de alturas entre izquierda y derecha)
// esto se usa para mantener el arbol balanceado
int factorBalance(viaje *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// rotacion hacia la derecha para balancear el arbol
// (parte del algoritmo AVL)
viaje *rotarDerecha(viaje *y) {
    viaje *x = y->izquierda;
    viaje *t2 = x->derecha;

    // hago la rotacion
    x->derecha = y;
    y->izquierda = t2;

    // actualizo las alturas
    y->altura = 1 + (altura(y->izquierda) > altura(y->derecha) ? altura(y->izquierda) : altura(y->derecha));
    x->altura = 1 + (altura(x->izquierda) > altura(x->derecha) ? altura(x->izquierda) : altura(x->derecha));

    return x;
}

// rotacion hacia la izquierda para balancear el arbol
viaje *rotarIzquierda(viaje *x) {
    viaje *y = x->derecha;
    viaje *t2 = y->izquierda;

    // hago la rotacion
    y->izquierda = x;
    x->derecha = t2;

    // actualizo las alturas
    x->altura = 1 + (altura(x->izquierda) > altura(x->derecha) ? altura(x->izquierda) : altura(x->derecha));
    y->altura = 1 + (altura(y->izquierda) > altura(y->derecha) ? altura(y->izquierda) : altura(y->derecha));

    return y;
}

// inserta un viaje en el arbol AVL
// mantiene el arbol balanceado automaticamente
viaje *insertarViaje(viaje *raiz, int codigo, int capacidad, int *insertado) {
    // caso base: si llegue al final, creo el nuevo nodo
    if (raiz == NULL) {
        viaje *nuevo = malloc(sizeof(viaje));
        if (nuevo == NULL) {
            printf("Problema de memoria! No se pudo crear el viaje.\n");
            *insertado = 0;
            return NULL;
        }
        // inicializo el nodo
        nuevo->codigoViaje = codigo;
        nuevo->capacidad = capacidad;
        nuevo->pasajerosEmbarcados = 0;
        nuevo->altura = 1;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        *insertado = 1;
        return nuevo;
    }

    // busco el lugar correcto para insertar
    if (codigo < raiz->codigoViaje) {
        raiz->izquierda = insertarViaje(raiz->izquierda, codigo, capacidad, insertado);
    } else if (codigo > raiz->codigoViaje) {
        raiz->derecha = insertarViaje(raiz->derecha, codigo, capacidad, insertado);
    } else {
        // el codigo ya existe
        printf("Ya existe un viaje con codigo %d!\n", codigo);
        *insertado = 0;
        return raiz;
    }

    // actualizo la altura del nodo actual
    raiz->altura = 1 + (altura(raiz->izquierda) > altura(raiz->derecha) ? altura(raiz->izquierda) : altura(raiz->derecha));

    // obtengo el factor de balance
    int balance = factorBalance(raiz);

    // casos para rotar hacia la derecha
    if (balance > 1 && codigo < raiz->izquierda->codigoViaje) {
        // rotacion simple a la derecha (LL)
        return rotarDerecha(raiz);
    }

    // casos para rotar hacia la izquierda
    if (balance < -1 && codigo > raiz->derecha->codigoViaje) {
        // rotacion simple a la izquierda (RR)
        return rotarIzquierda(raiz);
    }

    // rotacion doble LR
    if (balance > 1 && codigo > raiz->izquierda->codigoViaje) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    // rotacion doble RL
    if (balance < -1 && codigo < raiz->derecha->codigoViaje) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

// busca un viaje por su codigo en el arbol
viaje *buscarViaje(viaje *raiz, int codigo) {
    if (raiz == NULL) {
        return NULL; // no lo encontre
    }
    if (codigo == raiz->codigoViaje) {
        return raiz; // lo encontre!
    }
    // busco en el lado izquierdo o derecho segun sea menor o mayor
    if (codigo < raiz->codigoViaje) {
        return buscarViaje(raiz->izquierda, codigo);
    }
    return buscarViaje(raiz->derecha, codigo);
}

// muestra el arbol en forma visual
// nivel es para saber cuantos espacios dejar
void mostrarArbol(viaje *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }
    // primero muestro el lado derecho (arriba)
    mostrarArbol(raiz->derecha, nivel + 1);
    // luego el nodo actual con espacios para indentacion
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("Viaje %d | Cap: %d | Embarcados: %d | Alt: %d\n",
           raiz->codigoViaje, raiz->capacidad, raiz->pasajerosEmbarcados, raiz->altura);
    // y finalmente el lado izquierdo (abajo)
    mostrarArbol(raiz->izquierda, nivel + 1);
}

// cuenta cuantos viajes hay en el arbol
int contarViajes(viaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    // cuento este nodo mas los de la izquierda y derecha
    return 1 + contarViajes(raiz->izquierda) + contarViajes(raiz->derecha);
}

// suma todos los pasajeros embarcados en todos los viajes
int sumarEmbarcadosArbol(viaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    // sumo este nodo mas los de izquierda y derecha
    return raiz->pasajerosEmbarcados + sumarEmbarcadosArbol(raiz->izquierda) + sumarEmbarcadosArbol(raiz->derecha);
}

// libera toda la memoria del arbol
void liberarArbol(viaje *raiz) {
    if (raiz == NULL) {
        return;
    }
    // libero primero los hijos
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    // luego libero el nodo actual
    free(raiz);
}

// opcion del menu para registrar un viaje
void registrarViajePrograma(void) {
    int codigoDestino;
    printf("Codigo del destino donde va el viaje: ");
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

    // pido el codigo del viaje
    int codigoViaje;
    printf("Codigo del viaje (numero unico): ");
    if (scanf("%d", &codigoViaje) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // pido la capacidad
    int capacidad;
    printf("Cuantos pasajeros puede llevar este viaje: ");
    if (scanf("%d", &capacidad) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // valido que la capacidad sea positiva
    if (capacidad <= 0) {
        printf("La capacidad debe ser mayor que cero!\n");
        return;
    }

    // inserto el viaje en el arbol
    int insertado = 0;
    d->raizViajes = insertarViaje(d->raizViajes, codigoViaje, capacidad, &insertado);
    if (insertado) {
        printf("Viaje creado correctamente!\n");
    }
}

// opcion del menu para buscar un viaje
void buscarViajeMenu(void) {
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

    int codigoViaje;
    printf("Codigo del viaje que buscas: ");
    if (scanf("%d", &codigoViaje) != 1) {
        limpiarBuffer();
        printf("ERROR! Debes escribir un numero.\n");
        return;
    }
    limpiarBuffer();

    // busco el viaje en el arbol
    viaje *v = buscarViaje(d->raizViajes, codigoViaje);
    if (v == NULL) {
        printf("Ese viaje %d no existe en ese destino!\n", codigoViaje);
        return;
    }
    printf("\nViaje encontrado!!!\n");
    printf("Codigo: %d\n", v->codigoViaje);
    printf("Capacidad total: %d\n", v->capacidad);
    printf("Pasajeros ya embarcados: %d\n", v->pasajerosEmbarcados);
    printf("Altura en el arbol: %d\n", v->altura);
}

// opcion del menu para mostrar el arbol de viajes
void mostrarArbolMenu(void) {
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

    if (d->raizViajes == NULL) {
        printf("No hay viajes programados para ese destino aun.\n");
        return;
    }

    printf("\nArbol de viajes del destino %d:\n\n", codigoDestino);
    mostrarArbol(d->raizViajes, 0);
}
