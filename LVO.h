#ifndef LVO_H
#define LVO_H

#include "Elector.h"

#define INFINITO 999999999

typedef struct nodoLVO{

    Elector dato;
    struct nodoLVO *sig;
} NodoLVO;

typedef struct {
    NodoLVO *acc;
    NodoLVO *cur;
    NodoLVO *aux;
} LVO;

void insertLVO(LVO *lista, Elector nuevoDato, int *exito, double *costo);
void forwardLVO(LVO *lista);
void initLVO(LVO *lista);
void vaciarLVO(LVO *lista);
void liberarLVO(LVO *lista);
void supressLVO(LVO *lista, double *costo);
void copyLVO(LVO *lista, Elector *electo);
void resetLVO(LVO *lista);
// Funciones
void mostrarLVO(LVO lista);
void LocalizarLVO(LVO *lista, int dni, int *exito, int *costo);
void AltaLVO(LVO *lista, Elector nuevo, int *exito, double *costo);
void BajaLVO(LVO *lista, Elector borrar, int *exito, double *costo);
void EvocacionLVO(LVO *lista, int dni, Elector *electo, int *exito, int *costo);
#endif
