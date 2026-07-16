//Sistema de Gestión del Terminal Portuario Turístico de Buenaventura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Nodo pasajero 
typedef struct {
    int documento;
    char tipoDocumento[30];
    char estado [20];

    struct pasajero *siguiente;
} pasajero;

// cola fifo

typedef struct { 
    pasajero *frente;
    pasajero *final;
} cola;

//nodo del arbol de viajes 
typedef struct viaje {
    int codigoViaje;
    int capacidad;

    struct viaje *izquierda;
    struct viaje *derecha;
} viaje;

//destino

typedef struct destino {
  int codigo;
  char nombre[50];
  char empresa[50];
  cola colaPasajeros;
  viaje *raizViajes;

  struct destino *siguiente;

}destino;

destino *listaDestinos = NULL;

//Registro destino

void registrarDestino(){

    destino *nuevo = (destino *)malloc(sizeof(destino));

    printf("codigo: ");
    scanf("%d",&nuevo->codigo);

    getchar();

    printf("Nombre del destino: ");
    fgets(nuevo->nombre,50,stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

}