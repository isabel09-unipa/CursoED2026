#include <stdio.h>

struct Pasajero {
    char nombre[50];
    int edad;
    char genero[20];
};

int main() {
    struct Pasajero p;

    printf("Nombre: ");
    scanf(" %49[^\n]", p.nombre);

    printf("Edad: ");
    scanf("%d", &p.edad);

    printf("Genero: ");
    scanf(" %19s", p.genero);

    printf("\nNombre: %s\n", p.nombre);
    printf("Edad: %d\n", p.edad);
    printf("Genero: %s\n", p.genero);

    return 0;
}