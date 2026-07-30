#include <stdio.h>

void intercambiar(int *a, int *b); // No usado aquí pero para consistencia
void mostrarProgreso(char *metodo, char *estado);

void merge(int arreglo[], int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arreglo[izquierda + i];
    for(int i = 0; i < n2; i++)
        R[i] = arreglo[medio + 1 + i];

    int i = 0, j = 0, k = izquierda;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arreglo[k++] = L[i++];
        } else {
            arreglo[k++] = R[j++];
        }
    }

    while(i < n1)
        arreglo[k++] = L[i++];
    while(j < n2)
        arreglo[k++] = R[j++];
}

void mergeSort(int arreglo[], int izquierda, int derecha) {
    if(izquierda < derecha) {
        int medio = (izquierda + derecha) / 2;
        mergeSort(arreglo, izquierda, medio);
        mergeSort(arreglo, medio + 1, derecha);
        merge(arreglo, izquierda, medio, derecha);
    }
}

void mergeSortWrapper(int arreglo[], int cantidad) {
    mostrarProgreso("MergeSort", "Dividiendo y fusionando...");
    mergeSort(arreglo, 0, cantidad - 1);
}