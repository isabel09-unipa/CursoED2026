/* Taller Unidad 5
   Métodos de ordenamiento eficientes y búsqueda 
binaria en C
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 30

int pesos[MAX];
int original[MAX];
int cantidad;
int ordenado = 0;
int datosCargados = 0;

/* Prototipos */
void registrarPesos();
void generarPesos();
void mostrarPesos();
void restaurarOriginal();
void mostrarProceso();

void quickSort(int arr[], int inicio, int fin);

void mergeSort(int arr[], int izquierda, int derecha);
void merge(int arr[], int izquierda, int medio, int derecha);

void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);

int busquedaBinaria(int valor);

int main() {

    int opcion;
    int valor;
    int posicion;

    srand(time(NULL));

    printf("=====================================\n");
    printf(" SISTEMA DE CONTENEDORES PORTUARIOS\n");
    printf("=====================================\n");

    printf("Cantidad de contenedores (1-%d): ", MAX);
    scanf("%d", &cantidad);

    if(cantidad < 1 || cantidad > MAX) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    do {

        printf("\n=========== MENU ===========\n");
        printf("1. Registrar pesos manualmente\n");
        printf("2. Generar pesos aleatorios\n");
        printf("3. Mostrar arreglo actual\n");
        printf("4. Ordenar con QuickSort\n");
        printf("5. Ordenar con MergeSort\n");
        printf("6. Ordenar con HeapSort\n");
        printf("7. Buscar peso (Busqueda Binaria)\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {

            case 1:

                registrarPesos();
                break;

            case 2:

                generarPesos();
                break;

            case 3:

                mostrarPesos();
                break;

            case 4:

                if(!datosCargados) {
                    printf("Primero cargue los datos.\n");
                    break;
                }

                restaurarOriginal();

                printf("\n===== QUICKSORT =====\n");

                printf("Estado inicial:\n");
                mostrarPesos();

                quickSort(pesos, 0, cantidad - 1);

                printf("\nResultado final:\n");
                mostrarPesos();

                ordenado = 1;
                break;

            case 5:

                if(!datosCargados) {
                    printf("Primero cargue los datos.\n");
                    break;
                }

                restaurarOriginal();

                printf("\n===== MERGESORT =====\n");

                printf("Estado inicial:\n");
                mostrarPesos();

                mergeSort(pesos, 0, cantidad - 1);

                printf("\nResultado final:\n");
                mostrarPesos();

                ordenado = 1;
                break;

            case 6:

                if(!datosCargados) {
                    printf("Primero cargue los datos.\n");
                    break;
                }

                restaurarOriginal();

                printf("\n===== HEAPSORT =====\n");

                printf("Estado inicial:\n");
                mostrarPesos();

                heapSort(pesos, cantidad);

                printf("\nResultado final:\n");
                mostrarPesos();

                ordenado = 1;
                break;

            case 7:

                if(!ordenado) {

                    printf("Primero debe ordenar el arreglo.\n");

                } else {

                    printf("Ingrese el peso a buscar: ");
                    scanf("%d", &valor);

                    posicion = busquedaBinaria(valor);

                    if(posicion == -1)
                        printf("Peso no encontrado.\n");
                    else
                        printf("Peso encontrado en la posicion %d.\n",
                               posicion + 1);
                }

                break;

            case 0:

                printf("Programa finalizado.\n");
                break;

            default:

                printf("Opcion invalida.\n");
        }

    } while(opcion != 0);

    return 0;
}

/* Mostrar proceso */
void mostrarProceso() {

    int i;

    for(i = 0; i < cantidad; i++) {
        printf("%d ", pesos[i]);
    }

    printf("\n");
}

/* Registrar pesos */
void registrarPesos() {

    int i;

    for(i = 0; i < cantidad; i++) {

        printf("Ingrese el peso del contenedor %d: ", i + 1);
        scanf("%d", &pesos[i]);

        original[i] = pesos[i];
    }

    datosCargados = 1;
    ordenado = 0;

    printf("\nDatos registrados correctamente.\n");
}

/* Generar pesos aleatorios */
void generarPesos() {

    int i;

    for(i = 0; i < cantidad; i++) {

        pesos[i] = rand() % 30001 + 1000;
        original[i] = pesos[i];
    }

    datosCargados = 1;
    ordenado = 0;

    printf("\nPesos generados correctamente.\n");
}

/* Restaurar originales */
void restaurarOriginal() {

    int i;

    for(i = 0; i < cantidad; i++) {
        pesos[i] = original[i];
    }
}

/* Mostrar arreglo */
void mostrarPesos() {

    int i;

    printf("\n");

    for(i = 0; i < cantidad; i++) {
        printf("%d ", pesos[i]);
    }

    printf("\n");
}

/* QuickSort */
void quickSort(int arr[], int inicio, int fin) {

    int i = inicio;
    int j = fin;
    int pivote = arr[(inicio + fin) / 2];
    int aux;

    while(i <= j) {

        while(arr[i] < pivote)
            i++;

        while(arr[j] > pivote)
            j--;

        if(i <= j) {

            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;

            printf("Paso QuickSort: ");
            mostrarProceso();

            i++;
            j--;
        }
    }

    if(inicio < j)
        quickSort(arr, inicio, j);

    if(i < fin)
        quickSort(arr, i, fin);
}

/* Merge */
void merge(int arr[], int izquierda, int medio, int derecha) {

    int temp[MAX];
    int i = izquierda;
    int j = medio + 1;
    int k = izquierda;

    while(i <= medio && j <= derecha) {

        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= medio)
        temp[k++] = arr[i++];

    while(j <= derecha)
        temp[k++] = arr[j++];

    for(i = izquierda; i <= derecha; i++)
        arr[i] = temp[i];

    printf("Paso MergeSort: ");
    mostrarProceso();
}

/* MergeSort */
void mergeSort(int arr[], int izquierda, int derecha) {

    if(izquierda < derecha) {

        int medio = (izquierda + derecha) / 2;

        mergeSort(arr, izquierda, medio);
        mergeSort(arr, medio + 1, derecha);

        merge(arr, izquierda, medio, derecha);
    }
}

/* Heapify */
void heapify(int arr[], int n, int i) {

    int mayor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;
    int aux;

    if(izquierda < n && arr[izquierda] > arr[mayor])
        mayor = izquierda;

    if(derecha < n && arr[derecha] > arr[mayor])
        mayor = derecha;

    if(mayor != i) {

        aux = arr[i];
        arr[i] = arr[mayor];
        arr[mayor] = aux;

        heapify(arr, n, mayor);
    }
}

/* HeapSort */
void heapSort(int arr[], int n) {

    int i;
    int aux;

    for(i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for(i = n - 1; i > 0; i--) {

        aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;

        printf("Paso HeapSort: ");
        mostrarProceso();

        heapify(arr, i, 0);
    }
}

/* Busqueda Binaria */
int busquedaBinaria(int valor) {

    int izquierda = 0;
    int derecha = cantidad - 1;
    int medio;

    while(izquierda <= derecha) {

        medio = (izquierda + derecha) / 2;

        if(pesos[medio] == valor)
            return medio;

        if(pesos[medio] < valor)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }

    return -1;
}