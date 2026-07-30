# Sistema de Gestión del Terminal Portuario Turístico de Buenaventura

Proyecto en lenguaje C organizado en módulos para manejar destinos, pasajeros, viajes y estadísticas.

## Compilación

Desde la carpeta `ProyectoFinal3`, ejecute:

```bash
make
```

Luego ejecute el programa con:

```bash
./terminal_buenaventura
```

Para limpiar los archivos objeto y el ejecutable:

```bash
make clean
```

## Organización de archivos

- `estructuras.h`: define las estructuras `pasajero`, `cola`, `viaje` y `destino`.
- `utils.h` / `utils.c`: función `limpiarBuffer()` para descartar caracteres sobrantes del `stdin` tras `scanf`.
- `destinos.h` / `destinos.c`: manejo de la lista dinámica de destinos, registro, modificación, visualización y liberación de memoria.
- `pasajeros.h` / `pasajeros.c`: gestión de la cola FIFO de pasajeros por destino, incluyendo registro, embarque, consultas y liberación.
- `viajes.h` / `viajes.c`: árbol AVL de viajes por destino, con inserción balanceada, búsqueda, visualización y liberación.
- `estadisticas.h` / `estadisticas.c`: cálculo de estadísticas globales basadas en destinos, colas y árboles.
- `main.c`: menú principal y control de flujo del sistema.

## Cómo funciona

### Colas FIFO

Cada destino mantiene una `cola` dinámica de `pasajero`.
- Los pasajeros se encolan al final cuando se registran.
- Al embarcar, el sistema busca el primer pasajero con estado `en espera` y actualiza su estado a `embarcado`.
- Los nodos de pasajero no se eliminan al embarcar, lo que permite conservar el historial y consultar su ubicación.

### Árbol AVL

Cada destino tiene un árbol AVL de `viaje` independiente.
- El árbol usa `codigoViaje` como clave.
- Después de cada inserción, el árbol se rebalancea automáticamente con rotaciones LL, RR, LR o RL.
- El sistema imprime qué rotación se aplicó y el código del nodo afectado.

## Validaciones implementadas

- Validación de entradas numéricas en `scanf`.
- Limpieza del buffer de entrada (`limpiarBuffer`) tras cada lectura con `scanf`.
- Validación de códigos de destino únicos.
- Prevención de registro de pasajeros con documentos duplicados en cualquier destino.
- Validación de opciones de tipo de documento.
- Validación de capacidad de viaje mayor que cero.
- Verificación de existencias de destino y viaje antes de operar.

## Memoria dinámica

Todos los destinos, pasajeros y viajes se manejan con `malloc` y `free`.
La función `liberarDestinos()` libera todas las colas, árboles y nodos de destino antes de salir.
