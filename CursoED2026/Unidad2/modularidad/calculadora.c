#include <stdio.h>
#include "areas.h"
#include "volumenes.h"

int main(){

    float radio = 5;
    float lado = 4;

    printf("Area del circulo: %.2f\n", areaCirculo(radio));
    printf("Area del cuadrado: %.2f\n", areaCuadrado(lado));

    printf("Volumen de la esfera: %.2f\n", volumenEsfera(radio));
    printf("Volumen del cubo: %.2f\n", volumenCubo(lado));

    return 0;
}