int busquedaBinaria(int arreglo[], int cantidad, int valor) {
    int izquierda = 0;
    int derecha = cantidad - 1;

    while(izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;

        if(arreglo[medio] == valor)
            return medio;

        if(arreglo[medio] < valor)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return -1;
}