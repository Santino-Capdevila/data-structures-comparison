# Comparacion de estructuras de datos — Padron electoral

Practico de Maquina 1 — Estructuras de Datos y Algoritmos, UNSL, 2026.

Implementacion de un padron electoral sobre tres estructuras distintas y
comparacion del costo de dar de alta, dar de baja y consultar electores en
cada una.

**Integrantes:** Lorenzo Luna y Santino Capdevila (Grupo 15)

## Estructuras

- **LVO** — Lista vinculada ordenada con terminacion dada por contenido (centinela +infinito).
- **LSOBB** — Lista secuencial ordenada con busqueda binaria (biseccion, limites inclusivos, testigo a izquierda).
- **ABB** — Arbol binario de busqueda. En la baja con dos hijos usa la politica del menor de los mayores, con copia de datos.

## Modelo de costos

| Operacion | Como se mide |
|---|---|
| Alta y baja en LSOBB | 1 por cada corrimiento de elemento |
| Alta y baja en LVO y ABB | 0,5 por cada modificacion de puntero |
| Baja en ABB con reemplazo | + 1 por la copia de datos |
| Consultas | 1 por cada celda consultada |

## Resultados

Sobre las 8975 operaciones de `Operaciones_Padron.txt`, con un maximo de 2001
electores presentes al mismo tiempo:

| | Alta (prom / max) | Baja (prom / max) | Evocacion ok (prom / max) | Evocacion falla (prom / max) |
|---|---|---|---|---|
| **LSOBB** | 413,65 / 2000 | 503,36 / 2000 | 10,14 / 11 | 9,88 / 11 |
| **LVO** | 1,00 / 1,00 | 0,50 / 0,50 | 566,80 / 1994 | 463,47 / 1206 |
| **ABB** | 0,50 / 0,50 | 1,02 / 1,50 | 11,84 / 22 | 12,03 / 21 |

Ninguna de las tres gana en todo: la LSOBB es la mejor consultando y la peor
insertando, y la LVO es exactamente al reves. El ABB no es el mejor en ninguna
operacion, pero es el unico que no es malo en ninguna.

## Compilar y ejecutar

Con Code::Blocks: abrir `P1-Grupo15.cbp` y compilar.

Desde la terminal:

```
gcc -o padron main.c LVO.c LSOBB.c ABB.c Elector.c
```

El archivo `Operaciones_Padron.txt` tiene que quedar en la misma carpeta desde
la que se ejecuta el programa.
