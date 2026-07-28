// Estadisticas del terminal portuario
// Aqui mostramos datos interesantes sobre como va el negocio

#include <stdio.h>
#include "estadisticas.h"
#include "destinos.h"
#include "pasajeros.h"
#include "viajes.h"

// muestra varias estadisticas del sistema
void mostrarEstadisticas(void) {
    if (listaDestinos == NULL) {
        printf("No hay ningun destino aun, asi que no hay estadisticas.\n");
        return;
    }

    // variables para ir sumando datos
    destino *actual = listaDestinos;
    int destinosCount = 0;
    int sumaPasajerosEspera = 0;
    int sumaViajes = 0;
    int sumaEmbarcados = 0;
    destino *mayorEsperaDestino = NULL;
    destino *menorEsperaDestino = NULL;

    // recorro todos los destinos para sacar estadisticas
    while (actual != NULL) {
        int pasajerosEspera = contarPasajeros(actual);
        int viajesDestino = contarViajes(actual->raizViajes);
        int embarcadosDestino = sumarEmbarcadosArbol(actual->raizViajes);

        // voy sumando los totales
        sumaPasajerosEspera += pasajerosEspera;
        sumaViajes += viajesDestino;
        sumaEmbarcados += embarcadosDestino;
        destinosCount++;

        // busco cual tiene mas gente esperando
        if (mayorEsperaDestino == NULL || pasajerosEspera > contarPasajeros(mayorEsperaDestino)) {
            mayorEsperaDestino = actual;
        }
        // y cual tiene menos
        if (menorEsperaDestino == NULL || pasajerosEspera < contarPasajeros(menorEsperaDestino)) {
            menorEsperaDestino = actual;
        }

        actual = actual->siguiente;
    }

    // calculo los promedios
    double promedioEspera = destinosCount > 0 ? (double)sumaPasajerosEspera / destinosCount : 0.0;
    double promedioEmbarcadosPorViaje = sumaViajes > 0 ? (double)sumaEmbarcados / sumaViajes : 0.0;

    // muestro todo
    printf("\n========== ESTADISTICAS DEL SISTEMA ==========\n\n");
    printf("1. Promedio de pasajeros esperando por destino: %.2f\n", promedioEspera);
    printf("2. Promedio de pasajeros embarcados por viaje: %.2f\n", promedioEmbarcadosPorViaje);
    if (mayorEsperaDestino != NULL) {
        printf("3. Destino con MAS gente esperando: %s (codigo %d) con %d pasajeros\n",
               mayorEsperaDestino->nombre, mayorEsperaDestino->codigo, contarPasajeros(mayorEsperaDestino));
    } else {
        printf("3. No hay gente esperando en ningun lado.\n");
    }
    if (menorEsperaDestino != NULL) {
        printf("4. Destino con MENOS gente esperando: %s (codigo %d) con %d pasajeros\n",
               menorEsperaDestino->nombre, menorEsperaDestino->codigo, contarPasajeros(menorEsperaDestino));
    } else {
        printf("4. No hay gente esperando en ningun lado.\n");
    }
    printf("5. Total de pasajeros registrados hasta ahora: %d\n", totalRegistrados);
    printf("6. Total de pasajeros que ya se embarcaron: %d\n", totalEmbarcados);
    printf("\n============================================\n\n");
}
