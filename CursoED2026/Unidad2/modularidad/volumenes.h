#ifndef VOLUMENES_H
#define VOLUMENES_H

#include <math.h>

float volumenEsfera(float radio){
    return (4.0/3.0) * M_PI * radio * radio * radio;
}

float volumenCubo(float lado){
    return lado * lado * lado;
}

#endif