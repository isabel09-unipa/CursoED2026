//Sistema de Gestión del Terminal Portuario Turístico de Buenaventura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pasajero {
    int documento;
    char tipoDocumento[30];
    char estado[20];
    struct pasajero *siguiente;
} pasajero;

typedef struct {
    pasajero *frente;
    pasajero *final;
} cola;

typedef struct viaje {
    int codigoViaje;
    int capacidad;
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

destino *listaDestinos = NULL;

// Prototipos

destino *buscarDestino(int codigo);
void registrarDestino(void);
void mostrarDestinos(void);
void modificarDestino(void);
int contarPasajeros(destino *d);

void registrarDestino(void) {
    destino *nuevo = malloc(sizeof(destino));
    if (nuevo == NULL) {
        fprintf(stderr, "Error de memoria al crear el destino.\n");
        return;
    }

    printf("codigo: ");
    scanf("%d", &nuevo->codigo);
    getchar();

    printf("Nombre del destino: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    printf("empresa: ");
    fgets(nuevo->empresa, sizeof(nuevo->empresa), stdin);
    nuevo->empresa[strcspn(nuevo->empresa, "\n")] = '\0';

    nuevo->colaPasajeros.frente = NULL;
    nuevo->colaPasajeros.final = NULL;
    nuevo->raizViajes = NULL;
    nuevo->siguiente = NULL;

    if (listaDestinos == NULL) {
        listaDestinos = nuevo;
    } else {
        destino *aux = listaDestinos;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }

    printf("\nDestino registrado correctamente\n");
}

destino *buscarDestino(int codigo) {
    destino *aux = listaDestinos;
    while (aux != NULL) {
        if (aux->codigo == codigo) {
            return aux;
        }
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
        printf("\nCodigo : %d", aux->codigo);
        printf("\nDestino: %s", aux->nombre);
        printf("\nEmpresa: %s", aux->empresa);
        aux = aux->siguiente;
    }
}

void modificarDestino(void) {
    int codigo;
    printf("Ingrese codigo: ");
    scanf("%d", &codigo);
    getchar();

    destino *d = buscarDestino(codigo);
    if (d == NULL) {
        printf("\nDestino no encontrado\n");
        return;
    }

    printf("Nuevo nombre: ");
    fgets(d->nombre, sizeof(d->nombre), stdin);
    d->nombre[strcspn(d->nombre, "\n")] = '\0';

    printf("Nueva empresa: ");
    fgets(d->empresa, sizeof(d->empresa), stdin);
    d->empresa[strcspn(d->empresa, "\n")] = '\0';

    printf("\nDatos actualizados\n");
}

int contarPasajeros(destino *d) {
    int contador = 0;
    pasajero *aux = d->colaPasajeros.frente;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

int main(void) {
    int opcion;

    do {
        printf("\n=== SISTEMA DE GESTION DE DESTINOS ===\n");
        printf("1. Registrar destino\n");
        printf("2. Mostrar destinos\n");
        printf("3. Modificar destino\n");
        printf("4. Contar pasajeros de un destino\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcion = 0;
        }
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
            case 4: {
                int codigo;
                printf("Ingrese codigo del destino: ");
                if (scanf("%d", &codigo) != 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Entrada invalida.\n");
                    break;
                }
                getchar();
                destino *d = buscarDestino(codigo);
                if (d == NULL) {
                    printf("Destino no encontrado.\n");
                } else {
                    printf("Pasajeros en destino %d: %d\n", codigo, contarPasajeros(d));
                }
                break;
            }
            case 5:
                printf("Saliendo del sistema.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}

