#include <stdio.h>

void intercambiar(int *a, int *b);
void mostrarProgreso(char *metodo, char *estado);

void heapify(int arreglo[], int cantidad, int raiz) {
    int mayor = raiz;
    int izquierda = 2 * raiz + 1;
    int derecha = 2 * raiz + 2;

    if(izquierda < cantidad && arreglo[izquierda] > arreglo[mayor])
        mayor = izquierda;
    if(derecha < cantidad && arreglo[derecha] > arreglo[mayor])
        mayor = derecha;

    if(mayor != raiz) {
        intercambiar(&arreglo[raiz], &arreglo[mayor]);
        heapify(arreglo, cantidad, mayor);
    }
}

void heapSort(int arreglo[], int cantidad) {
    for(int i = cantidad / 2 - 1; i >= 0; i--)
        heapify(arreglo, cantidad, i);

    for(int i = cantidad - 1; i > 0; i--) {
        intercambiar(&arreglo[0], &arreglo[i]);
        heapify(arreglo, i, 0);
    }
}

void heapSortWrapper(int arreglo[], int cantidad) {
    mostrarProgreso("HeapSort", "Construyendo heap y extrayendo...");
    heapSort(arreglo, cantidad);
}