#ifndef VOLUMENES_H
#define VOLUMENES_H

#define PI 3.14159265358979323846

float volumenEsfera(float radio){
    return (4.0/3.0) * PI * radio * radio * radio;
}

float volumenCubo(float lado){
    return lado * lado * lado;
}

#endif