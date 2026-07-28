#include <stdio.h>
#include "estadisticas.h"
#include "destinos.h"
#include "pasajeros.h"
#include "viajes.h"

void mostrarEstadisticas(void) {
    if (listaDestinos == NULL) {
        printf("No hay destinos registrados para mostrar estadisticas.\n");
        return;
    }

    destino *actual = listaDestinos;
    int destinosCount = 0;
    int sumaPasajerosEspera = 0;
    int sumaViajes = 0;
    int sumaEmbarcados = 0;
    destino *mayorEsperaDestino = NULL;
    destino *menorEsperaDestino = NULL;

    while (actual != NULL) {
        int pasajerosEspera = contarPasajeros(actual);
        int viajesDestino = contarViajes(actual->raizViajes);
        int embarcadosDestino = sumarEmbarcadosArbol(actual->raizViajes);

        sumaPasajerosEspera += pasajerosEspera;
        sumaViajes += viajesDestino;
        sumaEmbarcados += embarcadosDestino;
        destinosCount++;

        if (mayorEsperaDestino == NULL || pasajerosEspera > contarPasajeros(mayorEsperaDestino)) {
            mayorEsperaDestino = actual;
        }
        if (menorEsperaDestino == NULL || pasajerosEspera < contarPasajeros(menorEsperaDestino)) {
            menorEsperaDestino = actual;
        }

        actual = actual->siguiente;
    }

    double promedioEspera = destinosCount > 0 ? (double)sumaPasajerosEspera / destinosCount : 0.0;
    double promedioEmbarcadosPorViaje = sumaViajes > 0 ? (double)sumaEmbarcados / sumaViajes : 0.0;

    printf("Estadisticas del sistema:\n");
    printf("1. Promedio de pasajeros en espera por destino: %.2f\n", promedioEspera);
    printf("2. Promedio de pasajeros embarcados por viaje: %.2f\n", promedioEmbarcadosPorViaje);
    if (mayorEsperaDestino != NULL) {
        printf("3. Destino con mayor cantidad de pasajeros en espera: %s (codigo %d) con %d pasajeros en espera\n",
               mayorEsperaDestino->nombre, mayorEsperaDestino->codigo, contarPasajeros(mayorEsperaDestino));
    } else {
        printf("3. No hay destinos con pasajeros en espera.\n");
    }
    if (menorEsperaDestino != NULL) {
        printf("4. Destino con menor cantidad de pasajeros en espera: %s (codigo %d) con %d pasajeros en espera\n",
               menorEsperaDestino->nombre, menorEsperaDestino->codigo, contarPasajeros(menorEsperaDestino));
    } else {
        printf("4. No hay destinos con pasajeros en espera.\n");
    }
    printf("5. Total registrados: %d\n", totalRegistrados);
    printf("6. Total embarcados: %d\n", totalEmbarcados);
}
