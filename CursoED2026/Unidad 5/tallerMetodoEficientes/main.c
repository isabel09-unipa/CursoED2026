/*
== UNIDAD 5 - METODOS DE ORDENAMIENTO ==

Yo agregue más cosas para mejor control y modifique la estructura

Autores:
Luis Alberto Gonzalez Arias
Valentina Alomia Montaño
Maria Isabel Sierra Garcia  (YO)
José Angel Perea Valencia
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quicksort.c"
#include "mergesort.c"
#include "heapsort.c"
#include "busquedaBin.c"

#define MAX_CONTENEDORES 30

// Prototipos codigo
void registrarPesos(int pesos[], int *cantidad);
void generarPesosAleatorios(int pesos[], int *cantidad);
void mostrarContenedores(int pesos[], int cantidad);
void copiarArreglo(int origen[], int destino[], int cantidad);

void quickSortWrapper(int arreglo[], int cantidad);
void mergeSortWrapper(int arreglo[], int cantidad);
void heapSortWrapper(int arreglo[], int cantidad);

int busquedaBinaria(int arreglo[], int cantidad, int valor);

void intercambiar(int *a, int *b);
void pausar();
void mostrarProgreso(char *metodo, char *estado);

// ====
// main 
// ====
int main() {
    int pesosOriginal[MAX_CONTENEDORES];
    int pesosTrabajo[MAX_CONTENEDORES];
    int cantidad = 0;
    int opcion;
    int ordenado = 0;

    srand(time(NULL));

    do {
        printf("\n============================================\n");
        printf("SISTEMA DE ORGANIZACION DE CONTENEDORES \"SAN JOSÉ PEREA VALENCIA S.A.S en alianza con SANTA MARIA RDP ESCC\"\n");
        printf("MUELLE VIRTUAL DE CARGA - MODULO AUXILIAR ENTREGAS JPV-Express\n");
        printf("===============================================\n");
        printf("1) Registrar peso de contenedores (para produccion empresarial)\n");
        printf("2) Generar pesos aleatorios de contenedores (para pruebas o snapshot)\n");
        printf("3) Mostrar contenedores registrados en sistema\n");
        printf("4) Ordenar contenedores metodo 1 (QuickSort Ord)\n");
        printf("5) Ordenar contenedores metodo 2 (MergeSort Ord)\n");
        printf("6) Ordenar contenedores metodo 3 (HeapSort Ord)\n");
        printf("7) Buscar contenedor (BUSQUEDA JPV)\n");
        printf("8) Salir del muelle virtual\n");
        printf("===============================================\n");
        printf("Seleccione una opcion de las anteriores: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                registrarPesos(pesosOriginal, &cantidad);
                copiarArreglo(pesosOriginal, pesosTrabajo, cantidad);
                ordenado = 0;
                break;

            case 2:
                generarPesosAleatorios(pesosOriginal, &cantidad);
                copiarArreglo(pesosOriginal, pesosTrabajo, cantidad);
                ordenado = 0; break;

            case 3:
                if (cantidad == 0) {
                    printf("\nNo hay contenedores registrados en el sistema JPV.\n");
                } else {
                    mostrarContenedores(pesosOriginal, cantidad);
                }
                pausar(); break;

            case 4:
                if (cantidad == 0) {
                    printf("\nNo hay datos para ordenar, registre datos para usar esta opción.\n");
                } else {
                    copiarArreglo(pesosOriginal, pesosTrabajo, cantidad);
                    mostrarProgreso("QuickSort", "Iniciando");
                    quickSortWrapper(pesosTrabajo, cantidad);
                    mostrarContenedores(pesosTrabajo, cantidad);
                    ordenado = 1;
                    mostrarProgreso("QuickSort", "Completado");
                }
                pausar(); break;

            case 5:
                if (cantidad == 0) {
                    printf("\nNo hay datos para ordenar, registre datos para usar esta opción.\n");
                } else {
                    copiarArreglo(pesosOriginal, pesosTrabajo, cantidad);
                    mostrarProgreso("MergeSort", "Iniciando");
                    mergeSortWrapper(pesosTrabajo, cantidad);
                    mostrarContenedores(pesosTrabajo, cantidad);
                    ordenado = 1;
                    mostrarProgreso("MergeSort", "Completado");
                }
                pausar(); break;

            case 6:
                if (cantidad == 0) {
                    printf("\nNo hay datos para ordenar, registre datos para usar esta opción.\n");
                } else {
                    copiarArreglo(pesosOriginal, pesosTrabajo, cantidad);
                    mostrarProgreso("HeapSort", "Iniciando");
                    heapSortWrapper(pesosTrabajo, cantidad);
                    mostrarContenedores(pesosTrabajo, cantidad);
                    ordenado = 1;
                    mostrarProgreso("HeapSort", "Completado");
                }
                pausar(); break;

            case 7:
                if (cantidad == 0) {
                    printf("\nNo hay contenedores registrados en el sistema JPV.\n");
                } else {
                    if (!ordenado) {
                        copiarArreglo(pesosOriginal, pesosTrabajo, cantidad);
                        quickSortWrapper(pesosTrabajo, cantidad);
                        ordenado = 1;
                        printf("\nEl arreglo fue ordenado automaticamente para la busqueda...\n");
                    }

                    int pesoBuscar;
                    printf("\nIngrese el peso a buscar: ");
                    scanf("%d", &pesoBuscar);

                    int posicion = busquedaBinaria(pesosTrabajo, cantidad, pesoBuscar);

                    if (posicion != -1) {
                        printf("\nContenedor encontrado en la posicion %d (peso: %d kg)\n", posicion, pesosTrabajo[posicion]);
                    } else {
                        printf("\nContenedor no encontrado.\n");
                    }
                }
                pausar(); break;

            case 8:
                printf("\nPOWERED BY JPVExpress.\n");
                printf("\nPrograma finalizado. Gracias por usar el sistema JPV.\n");
                break;

            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
                pausar();
        }

    } while(opcion != 8);

    return 0;
}

// =======
// GENERAL 
// =======
void registrarPesos(int pesos[], int *cantidad) {
    printf("\nCantidad de contenedores (1-%d): ", MAX_CONTENEDORES);
    scanf("%d", cantidad);

    if(*cantidad < 1 || *cantidad > MAX_CONTENEDORES) {
        printf("\nCantidad invalidia.\n");
        *cantidad = 0;
        return;
    }

    for(int i = 0; i < *cantidad; i++) {
        printf("Peso del contenedor %d (kg): ", i + 1);
        scanf("%d", &pesos[i]);
    }
    printf("\nRegistro completado exitosamente.\n");
}

void generarPesosAleatorios(int pesos[], int *cantidad) {
    printf("\nCantidad de contenedores (1-%d): ", MAX_CONTENEDORES);
    scanf("%d", cantidad);

    if(*cantidad < 1 || *cantidad > MAX_CONTENEDORES) {
        printf("\nCantidad invalida.\n");
        *cantidad = 0;
        return;
    }

    for(int i = 0; i < *cantidad; i++) {
        pesos[i] = 1000 + rand() % 44001;  // Rango 1000 - 45000 kg
    }
    printf("\nPesos generados aleatoriamente correctamente.\n");
}

void mostrarContenedores(int pesos[], int cantidad) {
    printf("\n=== CONTENEDORESs REGISTRADOS (%d) ===\n", cantidad);
    for(int i = 0; i < cantidad; i++) {
        printf("[%2d] %d kg\n", i, pesos[i]);
    }
    printf("==================================\n");
}

void copiarArreglo(int origen[], int destino[], int cantidad) {
    for(int i = 0; i < cantidad; i++) {
        destino[i] = origen[i];
    }
}

void intercambiar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void pausar() {
    printf("\nPresione ENTER para continuar...");
    while(getchar() != '\n');
    getchar();
}

void mostrarProgreso(char *metodo, char *estado) {
    printf("\n====================================\n");
    printf("Metodo: %s\n", metodo);
    printf("Estado actual: %s\n", estado);
    printf("====================================\n");
}