#include <stdio.h>

void intercambiar(int *a, int *b);
void mostrarProgreso(char *metodo, char *estado);

int particion(int arreglo[], int inicio, int fin) {
    int pivote = arreglo[fin];
    int i = inicio - 1;

    for(int j = inicio; j < fin; j++) {
        if(arreglo[j] < pivote) {
            i++;
            intercambiar(&arreglo[i], &arreglo[j]);
        }
    }
    intercambiar(&arreglo[i + 1], &arreglo[fin]);
    return i + 1;
}

void quickSort(int arreglo[], int inicio, int fin) {
    if(inicio < fin) {
        int pivote = particion(arreglo, inicio, fin);
        quickSort(arreglo, inicio, pivote - 1);
        quickSort(arreglo, pivote + 1, fin);
    }
}

void quickSortWrapper(int arreglo[], int cantidad) {
    mostrarProgreso("QuickSort", "Procesando particiones...");
    quickSort(arreglo, 0, cantidad - 1);
}