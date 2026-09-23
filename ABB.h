#ifndef ABB_H
#define ABB_H
#include "Elector.h"
typedef struct NodoABB{
Elector dato;
struct NodoABB *arbIzq;
struct NodoABB *arbDer;
}NodoABB;



typedef struct{
    NodoABB *raiz;
    NodoABB *cur;
    NodoABB *padre;
}ABB;

void initABB(ABB *arbol);
void vaciarABB(ABB *arbol);
void supressABB(ABB *arbol, double *costo);
void insertABB(ABB *arbol, Elector nuevo, int *exito, double *costo);
void resetABB(ABB *arbol);
void forwardIzqABB(ABB *arbol);
void forwardDerABB(ABB *arbol);
//Funciones
void mostrarABB(ABB arbol);
void LocalizarABB(ABB *arbol, int dni, int *exito, int *costo);
void AltaABB(ABB *arbol, Elector nuevo, int *exito, double *costo);
void BajaABB(ABB *arbol, Elector borrar, int *exito, double *costo);
void EvocacionABB(ABB *arbol, int dni, Elector *electo, int *exito, int *costo);
void preordenABB(NodoABB *nodo, int *cont, int *pag);


#endif
