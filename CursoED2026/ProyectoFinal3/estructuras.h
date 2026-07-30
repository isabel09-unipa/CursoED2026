// Definicion de las estructuras principales del programa
// Aqui defino los tipos de datos que usamos en todo el proyecto

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// estructura para representar a un pasajero
typedef struct pasajero {
    int documento;           // numero del documento unico
    char tipoDocumento[30];  // cedula, pasaporte, etc
    char estado[20];         // "en espera" o "embarcado"
    int viajeAsociado;       // codigo del viaje en el que va
    struct pasajero *siguiente;  // apuntador al siguiente pasajero en la cola
} pasajero;

// estructura para la cola de pasajeros
// (lista enlazada con dos apuntadores: inicio y final)
typedef struct cola {
    pasajero *frente;  // el primer pasajero en espera
    pasajero *final;   // el ultimo pasajero en espera
} cola;

// estructura para un viaje (nodo del arbol AVL)
typedef struct viaje {
    int codigoViaje;           // numero unico del viaje
    int capacidad;             // cuantos pasajeros puede llevar
    int pasajerosEmbarcados;   // cuantos pasajeros ya estan adentro
    int altura;                // altura del nodo en el arbol AVL
    struct viaje *izquierda;   // apuntador al hijo izquierdo
    struct viaje *derecha;     // apuntador al hijo derecho
} viaje;

// estructura para un destino
typedef struct destino {
    int codigo;              // numero unico del destino
    char nombre[50];         // nombre del lugar (ej: Cartagena)
    char empresa[50];        // empresa que lo maneja
    cola colaPasajeros;      // la cola de pasajeros esperando
    viaje *raizViajes;       // el arbol de viajes para este destino
    struct destino *siguiente;  // apuntador al siguiente destino
} destino;

#endif // ESTRUCTURAS_H
