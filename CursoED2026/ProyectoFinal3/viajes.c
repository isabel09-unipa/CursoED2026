#include <stdio.h>
#include <stdlib.h>
#include "viajes.h"
#include "destinos.h"
#include "utils.h"

int altura(viaje *nodo) {
    return nodo == NULL ? 0 : nodo->altura;
}

int factorBalance(viaje *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

viaje *rotarDerecha(viaje *y) {
    viaje *x = y->izquierda;
    viaje *t2 = x->derecha;

    x->derecha = y;
    y->izquierda = t2;

    y->altura = 1 + (altura(y->izquierda) > altura(y->derecha) ? altura(y->izquierda) : altura(y->derecha));
    x->altura = 1 + (altura(x->izquierda) > altura(x->derecha) ? altura(x->izquierda) : altura(x->derecha));

    return x;
}

viaje *rotarIzquierda(viaje *x) {
    viaje *y = x->derecha;
    viaje *t2 = y->izquierda;

    y->izquierda = x;
    x->derecha = t2;

    x->altura = 1 + (altura(x->izquierda) > altura(x->derecha) ? altura(x->izquierda) : altura(x->derecha));
    y->altura = 1 + (altura(y->izquierda) > altura(y->derecha) ? altura(y->izquierda) : altura(y->derecha));

    return y;
}

viaje *insertarViaje(viaje *raiz, int codigo, int capacidad, int *insertado) {
    if (raiz == NULL) {
        viaje *nuevo = malloc(sizeof(viaje));
        if (nuevo == NULL) {
            printf("Error de memoria al registrar el viaje.\n");
            *insertado = 0;
            return NULL;
        }
        nuevo->codigoViaje = codigo;
        nuevo->capacidad = capacidad;
        nuevo->pasajerosEmbarcados = 0;
        nuevo->altura = 1;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        *insertado = 1;
        return nuevo;
    }

    if (codigo < raiz->codigoViaje) {
        raiz->izquierda = insertarViaje(raiz->izquierda, codigo, capacidad, insertado);
    } else if (codigo > raiz->codigoViaje) {
        raiz->derecha = insertarViaje(raiz->derecha, codigo, capacidad, insertado);
    } else {
        printf("El viaje con codigo %d ya existe.\n", codigo);
        *insertado = 0;
        return raiz;
    }

    raiz->altura = 1 + (altura(raiz->izquierda) > altura(raiz->derecha) ? altura(raiz->izquierda) : altura(raiz->derecha));

    int balance = factorBalance(raiz);

    if (balance > 1 && codigo < raiz->izquierda->codigoViaje) {
        printf("Rotacion LL en el nodo %d\n", raiz->codigoViaje);
        return rotarDerecha(raiz);
    }

    if (balance < -1 && codigo > raiz->derecha->codigoViaje) {
        printf("Rotacion RR en el nodo %d\n", raiz->codigoViaje);
        return rotarIzquierda(raiz);
    }

    if (balance > 1 && codigo > raiz->izquierda->codigoViaje) {
        printf("Rotacion LR en el nodo %d\n", raiz->codigoViaje);
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    if (balance < -1 && codigo < raiz->derecha->codigoViaje) {
        printf("Rotacion RL en el nodo %d\n", raiz->codigoViaje);
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

viaje *buscarViaje(viaje *raiz, int codigo) {
    if (raiz == NULL) {
        return NULL;
    }
    if (codigo == raiz->codigoViaje) {
        return raiz;
    }
    if (codigo < raiz->codigoViaje) {
        return buscarViaje(raiz->izquierda, codigo);
    }
    return buscarViaje(raiz->derecha, codigo);
}

void mostrarArbol(viaje *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }
    mostrarArbol(raiz->derecha, nivel + 1);
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("Codigo: %d | Capacidad: %d | Embarcados: %d | Altura: %d\n",
           raiz->codigoViaje, raiz->capacidad, raiz->pasajerosEmbarcados, raiz->altura);
    mostrarArbol(raiz->izquierda, nivel + 1);
}

int contarViajes(viaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarViajes(raiz->izquierda) + contarViajes(raiz->derecha);
}

int sumarEmbarcadosArbol(viaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return raiz->pasajerosEmbarcados + sumarEmbarcadosArbol(raiz->izquierda) + sumarEmbarcadosArbol(raiz->derecha);
}

void liberarArbol(viaje *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    free(raiz);
}

void registrarViajePrograma(void) {
    int codigoDestino;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se registro el viaje.\n");
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
        printf("Entrada invalida. No se registro el viaje.\n");
        return;
    }
    limpiarBuffer();

    int capacidad;
    printf("Ingrese la capacidad del viaje: ");
    if (scanf("%d", &capacidad) != 1) {
        limpiarBuffer();
        printf("Entrada invalida. No se registro el viaje.\n");
        return;
    }
    limpiarBuffer();

    if (capacidad <= 0) {
        printf("La capacidad debe ser mayor a cero.\n");
        return;
    }

    int insertado = 0;
    d->raizViajes = insertarViaje(d->raizViajes, codigoViaje, capacidad, &insertado);
    if (insertado) {
        printf("Viaje registrado correctamente.\n");
    }
}

void buscarViajeMenu(void) {
    int codigoDestino;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("Entrada invalida.\n");
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
        printf("Entrada invalida.\n");
        return;
    }
    limpiarBuffer();

    viaje *v = buscarViaje(d->raizViajes, codigoViaje);
    if (v == NULL) {
        printf("Viaje con codigo %d no encontrado para el destino %d.\n", codigoViaje, codigoDestino);
        return;
    }
    printf("Viaje encontrado:\n");
    printf("Codigo: %d\n", v->codigoViaje);
    printf("Capacidad: %d\n", v->capacidad);
    printf("Pasajeros embarcados: %d\n", v->pasajerosEmbarcados);
    printf("Altura: %d\n", v->altura);
}

void mostrarArbolMenu(void) {
    int codigoDestino;
    printf("Ingrese el codigo del destino: ");
    if (scanf("%d", &codigoDestino) != 1) {
        limpiarBuffer();
        printf("Entrada invalida.\n");
        return;
    }
    limpiarBuffer();

    destino *d = buscarDestino(codigoDestino);
    if (d == NULL) {
        printf("Destino con codigo %d no encontrado.\n", codigoDestino);
        return;
    }

    if (d->raizViajes == NULL) {
        printf("No hay viajes programados para el destino %d.\n", codigoDestino);
        return;
    }

    mostrarArbol(d->raizViajes, 0);
}
