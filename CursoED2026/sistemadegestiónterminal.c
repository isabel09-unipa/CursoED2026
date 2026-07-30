//Sistema de Gestión del Terminal Portuario Turístico de Buenaventura

//Sistema de Gestión del Terminal Portuario Turístico de Buenaventura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Nodo pasajero
typedef struct pasajero {
    int documento;
    char tipoDocumento[30];
    char estado[20];

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
} destino;

destino *listaDestinos = NULL;

//Registro destino
void registrarDestino(void) {
    destino *nuevo = (destino *) malloc(sizeof(destino));
    if (nuevo == NULL) {
        printf("\nError: no se pudo reservar memoria\n");
        return;
    }

    printf("Ingrese codigo: ");
    scanf("%d", &nuevo->codigo);
    getchar();

    printf("Ingrese nombre del destino: ");
    fgets(nuevo->nombre, 50, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    printf("Ingrese empresa: ");
    fgets(nuevo->empresa, 50, stdin);
    nuevo->empresa[strcspn(nuevo->empresa, "\n")] = '\0';

    nuevo->colaPasajeros.frente = NULL;
    nuevo->colaPasajeros.final = NULL;
    nuevo->raizViajes = NULL;

    nuevo->siguiente = listaDestinos;
    listaDestinos = nuevo;

    printf("\nDestino registrado correctamente\n");
}

destino *buscardestino(int codigo) {
    destino *aux = listaDestinos;

    while (aux != NULL) {
        if (aux->codigo == codigo)
            return aux;

        aux = aux->siguiente;
    }

    return NULL;
}

void mostrarDestinos(void) {
    destino *aux = listaDestinos;

    if (aux == NULL) {
        printf("\nNo existen destinos registrados\n");
        return;
    }

    while (aux != NULL) {
        printf("\n====================");
        printf("\nCodigo: %d", aux->codigo);
        printf("\nDestino: %s", aux->nombre);
        printf("\nEmpresa: %s", aux->empresa);

        aux = aux->siguiente;
    }
    printf("\n====================\n");
}

//Modificar destino
void modificarDestino(void) {
    int codigo;

    printf("Ingrese codigo: ");
    scanf("%d", &codigo);
    getchar();

    destino *d = buscardestino(codigo);

    if (d == NULL) {
        printf("\nDestino no encontrado\n");
        return;
    }

    printf("Nuevo nombre: ");
    fgets(d->nombre, 50, stdin);
    d->nombre[strcspn(d->nombre, "\n")] = '\0';

    printf("Nueva empresa: ");
    fgets(d->empresa, 50, stdin);
    d->empresa[strcspn(d->empresa, "\n")] = '\0';

    printf("\nDatos actualizados\n");
}

int main(void) {
    int opcion;

    do {
        printf("\n--- Terminal Portuario Turistico de Buenaventura ---\n");
        printf("1. Registrar destino\n");
        printf("2. Mostrar destinos\n");
        printf("3. Modificar destino\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                registrarDestino();
                break;
            case 2:
                mostrarDestinos();
                break;
            case 3:
                modificarDestino();
                break;
            case 0:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida\n");
        }
    } while (opcion != 0);

    return 0;
}