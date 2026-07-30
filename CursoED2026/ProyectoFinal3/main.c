// Sistema de Terminal Portuario - Proyecto de Estructuras de Datos
// Hecho por: Estudiante
// Fecha: 2026

#include <stdio.h>
#include <stdlib.h>
#include "destinos.h"
#include "pasajeros.h"
#include "viajes.h"
#include "estadisticas.h"
#include "utils.h"

// funcion principal del programa
int main(void) {
    int opcion = -1;
    
    // el menu se repite hasta que el usuario seleccione salir (opcion 0)
    do {
        printf("\n================================\n");
        printf("TERMINAL PORTUARIO BUENAVENTURA\n");
        printf("================================\n");
        printf("1. Agregar destino\n");
        printf("2. Registrar un pasajero\n");
        printf("3. Ver pasajeros por destino\n");
        printf("4. Crear viaje\n");
        printf("5. Buscar un viaje\n");
        printf("6. Ver el arbol de viajes\n");
        printf("7. Embarcar pasajero\n");
        printf("8. Ver datos del pasajero\n");
        printf("9. Cambiar info del destino\n");
        printf("10. Listar todos los destinos\n");
        printf("11. Ver estadisticas\n");
        printf("0. SALIR\n");
        printf("================================\n");
        printf("Elige una opcion: ");

        // leo la opcion del usuario
        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer();
            printf("ERROR! Escribe un numero valido.\n");
            opcion = -1;
            continue;
        }
        limpiarBuffer();

        // dependiendo de lo que eligio, ejecuto una funcion u otra
        switch (opcion) {
            case 1:
                registrarDestino();
                break;
            case 2:
                registrarPasajero();
                break;
            case 3:
                mostrarPasajerosDestinoMenu();
                break;
            case 4:
                registrarViajePrograma();
                break;
            case 5:
                buscarViajeMenu();
                break;
            case 6:
                mostrarArbolMenu();
                break;
            case 7:
                embarcarPasajero();
                break;
            case 8:
                consultarUbicacionPasajero();
                break;
            case 9:
                modificarDestino();
                break;
            case 10:
                mostrarDestinos();
                break;
            case 11:
                mostrarEstadisticas();
                break;
            case 0:
                // cuando es 0 sale del ciclo
                break;
            default:
                printf("Esa opcion no existe, intenta de nuevo!\n");
                break;
        }
    } while (opcion != 0);

    // cuando salimos, liberamos la memoria que usamos
    liberarDestinos();
    printf("\nMemoria limpiada... Adios!\n");
    return 0;
}
