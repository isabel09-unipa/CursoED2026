#include <stdio.h>
#include <stdlib.h>
#include "destinos.h"
#include "pasajeros.h"
#include "viajes.h"
#include "estadisticas.h"
#include "utils.h"

int main(void) {
    int opcion = -1;
    do {
        printf("\n--- Sistema de Gestion del Terminal Portuario Turistico de Buenaventura ---\n");
        printf("1. Registrar destino\n");
        printf("2. Registrar pasajero\n");
        printf("3. Mostrar pasajeros por destino\n");
        printf("4. Registrar viaje programado\n");
        printf("5. Buscar viaje\n");
        printf("6. Mostrar arbol de viajes\n");
        printf("7. Realizar embarque\n");
        printf("8. Consultar pasajero\n");
        printf("9. Modificar destino\n");
        printf("10. Mostrar todos los destinos\n");
        printf("11. Mostrar estadisticas\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer();
            printf("Entrada invalida. Intente de nuevo.\n");
            opcion = -1;
            continue;
        }
        limpiarBuffer();

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
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);

    liberarDestinos();
    printf("Memoria liberada. Saliendo del sistema.\n");
    return 0;
}
