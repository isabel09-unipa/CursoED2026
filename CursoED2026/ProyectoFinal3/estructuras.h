#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct pasajero {
    int documento;
    char tipoDocumento[30];
    char estado[20];
    int viajeAsociado;
    struct pasajero *siguiente;
} pasajero;

typedef struct cola {
    pasajero *frente;
    pasajero *final;
} cola;

typedef struct viaje {
    int codigoViaje;
    int capacidad;
    int pasajerosEmbarcados;
    int altura;
    struct viaje *izquierda;
    struct viaje *derecha;
} viaje;

typedef struct destino {
    int codigo;
    char nombre[50];
    char empresa[50];
    cola colaPasajeros;
    viaje *raizViajes;
    struct destino *siguiente;
} destino;

#endif // ESTRUCTURAS_H
