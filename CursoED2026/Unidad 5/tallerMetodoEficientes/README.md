// Hecho con IA

# Sistema de Organización de Contenedores - Muelle Virtual JPV

## Información del Proyecto

**Asignatura:** Estructura de Datos  
**Unidad:** 5 - Métodos de Ordenamiento Eficientes y Búsqueda Binaria  
**Universidad:** Universidad del Pacífico  
**Fecha de Entrega:** 4 de junio de 2026

---

## Descripción

Este programa permite gestionar el peso de hasta 30 contenedores en un patio de carga portuaria. Implementa **tres métodos de ordenamiento eficientes** (QuickSort, MergeSort y HeapSort) y **búsqueda binaria**, cumpliendo con todos los requisitos del taller de la Unidad 5.

El sistema simula un **Muelle Virtual de Carga** con interfaz amigable mediante menú.

---

## Autor

- **José Angel Perea Valencia**

### Integrantes del Equipo
- Luis Alberto Gonzalez Arias
- Valentina Alomia Montaño
- Maria Isabel Sierra Garcia
- **José Angel Perea Valencia**

---

## Funcionalidades

- **Registro manual** de pesos de contenedores
- **Generación aleatoria** de pesos (rango: 1000 - 45000 kg)
- **Visualización** de contenedores registrados
- **Ordenamiento** mediante tres algoritmos eficientes:
  - QuickSort (Método 1)
  - MergeSort (Método 2)
  - HeapSort (Método 3)
- **Búsqueda Binaria** sobre el arreglo ordenado
- Indicadores de progreso y pausas para mejor experiencia de usuario
- Código modular y organizado en múltiples archivos

---

## Requisitos Técnicos

- Lenguaje: **C**
- Editor recomendado: **Visual Studio Code**
- Compilador: **GCC**
- Librerías utilizadas:
  - `<stdio.h>`
  - `<stdlib.h>`
  - `<time.h>`

---

## Estructura del Proyecto
unidad5/tallerMetodosEficientes/
├── main.c                    # Archivo principal y menú
├── quicksort.c               # Implementación de QuickSort
├── mergesort.c               # Implementación de MergeSort
├── heapsort.c                # Implementación de HeapSort
├── busquedaBin.c             # Implementación de Busqueda Binaria de elementos
├── README.md                 # Este archivo
└── evidencias/               # Capturas de pantalla

---

## Cómo Compilar y Ejecutar

### Opción 1: Compilación directa

```bash
gcc main.c quicksort.c mergesort.c heapsort.c -o contenedores -Wall -std=c99
./contenedores