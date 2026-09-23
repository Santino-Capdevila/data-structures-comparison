
#include "ABB.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void initABB(ABB *arbol)
{
    (*arbol).raiz = NULL;
    (*arbol).cur = NULL;
    (*arbol).padre = NULL;
}

void forwardIzqABB(ABB *arbol)
{
    (*arbol).padre = (*arbol).cur;
    (*arbol).cur = (*(*arbol).cur).arbIzq;
}

void forwardDerABB(ABB *arbol)
{
    (*arbol).padre = (*arbol).cur;
    (*arbol).cur = (*(*arbol).cur).arbDer;
}


void resetABB(ABB *arbol)
{
    (*arbol).cur = (*arbol).raiz;
    (*arbol).padre = (*arbol).raiz;
}

void insertABB(ABB *arbol, Elector nuevoDato, int *exito, double *costo)
{
    int dniNuevo, dniPadre;
    NodoABB *nodo = (NodoABB *)malloc(sizeof(NodoABB));
    *exito = -1;
    *costo = 0;
    if (nodo == NULL)
    {
        (*arbol).cur = NULL;
        return;
    }
    (*nodo).dato = nuevoDato;
    (*nodo).arbIzq = NULL;
    (*nodo).arbDer = NULL;

    if ((*arbol).raiz == NULL){
        (*arbol).raiz = nodo;
    }else{
        getDni(&nuevoDato, &dniNuevo);
        getDni(&(*(*arbol).padre).dato, &dniPadre);
        if (dniNuevo < dniPadre){
            (*(*arbol).padre).arbIzq = nodo;
        }else{
            (*(*arbol).padre).arbDer = nodo;
        }
    }
    *costo = *costo + 0.5;

    (*arbol).cur = nodo;
    *exito = 1;
}

void supressABB(ABB *arbol, double *costo){
    NodoABB *reemplazo;
    NodoABB *aBorrar;
    Elector copia;

    *costo = 0;
   
    if ((*(*arbol).cur).arbIzq != NULL && (*(*arbol).cur).arbDer != NULL){
        aBorrar = (*arbol).cur;

        forwardDerABB(arbol);
        while ((*(*arbol).cur).arbIzq != NULL){
            forwardIzqABB(arbol);
        }

        copia = (*(*arbol).cur).dato;
        (*aBorrar).dato = copia;
        *costo = *costo + 1;
    }

  
    if ((*(*arbol).cur).arbIzq != NULL){
        reemplazo = (*(*arbol).cur).arbIzq;
    }else{
        reemplazo = (*(*arbol).cur).arbDer;
    }

    if ((*arbol).cur == (*arbol).raiz){
        (*arbol).raiz = reemplazo;
    }else if ((*(*arbol).padre).arbIzq == (*arbol).cur){
        (*(*arbol).padre).arbIzq = reemplazo;
    }else{
        (*(*arbol).padre).arbDer = reemplazo;
    }
    *costo = *costo + 0.5;

    
    free((*arbol).cur);
    (*arbol).cur = reemplazo;
}

void LocalizarABB(ABB *arbol, int dni, int *exito, int *costo){
    int dniActual;

    *exito = 0;
    *costo = 0;
    resetABB(arbol);
    while ((*arbol).cur != NULL){
        getDni(&(*(*arbol).cur).dato, &dniActual);
        *costo = *costo + 1;
        if (dniActual == dni){
            *exito = 1;
            return;
        }
        if (dniActual < dni){
            forwardDerABB(arbol);
        }else{
            forwardIzqABB(arbol);
        }
    }
}

void AltaABB(ABB *arbol, Elector nuevo, int *exito, double *costo){
    int encontrado;
    int dni;
    int costoBusqueda;

    *exito = 0;
    *costo = 0;
    getDni(&nuevo, &dni);
    LocalizarABB(arbol, dni, &encontrado, &costoBusqueda);

    if (encontrado == 1){
        return;
    }

    insertABB(arbol, nuevo, exito, costo);
}

void BajaABB(ABB *arbol, Elector borrar, int *exito, double *costo){
    int encontrado;
    int dni;
    int costoBusqueda;
    int coinciden;
    char nombreApellidoGuardado[51], nombreApellidoBorrar[51];
    char domicilioGuardado[81], domicilioBorrar[81];
    int codigoPostalGuardado, codigoPostalBorrar;
    int mesaGuardado, mesaBorrar;
    int circuitoGuardado, circuitoBorrar;

    *exito = 0;
    *costo = 0;
    getDni(&borrar, &dni);
    LocalizarABB(arbol, dni, &encontrado, &costoBusqueda);

    if (encontrado == 0){
        return;
    }

    getNombreApellido(&((*(*arbol).cur).dato), nombreApellidoGuardado);
    getNombreApellido(&borrar, nombreApellidoBorrar);
    getDomicilio(&((*(*arbol).cur).dato), domicilioGuardado);
    getDomicilio(&borrar, domicilioBorrar);
    getCodigoPostal(&((*(*arbol).cur).dato), &codigoPostalGuardado);
    getCodigoPostal(&borrar, &codigoPostalBorrar);
    getMesa(&((*(*arbol).cur).dato), &mesaGuardado);
    getMesa(&borrar, &mesaBorrar);
    getCircuito(&((*(*arbol).cur).dato), &circuitoGuardado);
    getCircuito(&borrar, &circuitoBorrar);

    coinciden = stricmp(nombreApellidoGuardado, nombreApellidoBorrar) == 0 &&
                stricmp(domicilioGuardado, domicilioBorrar) == 0 &&
                codigoPostalGuardado == codigoPostalBorrar &&
                mesaGuardado == mesaBorrar &&
                circuitoGuardado == circuitoBorrar;

    if (coinciden == 0){
        return;
    }

    supressABB(arbol, costo);
    *exito = 1;
}

void EvocacionABB(ABB *arbol, int dni, Elector *electo, int *exito, int *costo){
    LocalizarABB(arbol, dni, exito, costo);
    if (*exito == 0){
        return;
    }
    *electo = (*(*arbol).cur).dato;
}

void preordenABB(NodoABB *nodo, int *cont, int *pag){
    int dni;
    char nombreApellido[51];
    char domicilio[81];
    int codigoPostal;
    int mesa;
    int circuito;
    if (nodo == NULL){
        return;
    }

    getDni(&((*nodo).dato), &dni);
    getNombreApellido(&((*nodo).dato), nombreApellido);
    getDomicilio(&((*nodo).dato), domicilio);
    getCodigoPostal(&((*nodo).dato), &codigoPostal);
    getMesa(&((*nodo).dato), &mesa);
    getCircuito(&((*nodo).dato), &circuito);

    printf("Nombre: %s\n", nombreApellido);
    printf("DNI: %d\n", dni);
    printf("Domicilio: %s\n", domicilio);
    printf("Codigo Postal: %d\n", codigoPostal);
    printf("Mesa: %d\n", mesa);
    printf("Circuito: %d\n", circuito);

    if ((*nodo).arbIzq == NULL && (*nodo).arbDer == NULL){
        printf("No tiene hijos\n");
    }else{
        if ((*nodo).arbIzq != NULL){
            getDni(&(*(*nodo).arbIzq).dato, &dni);
            printf("Hijo izquierdo: %d\n", dni);
        }
        if ((*nodo).arbDer != NULL){
            getDni(&(*(*nodo).arbDer).dato, &dni);
            printf("Hijo derecho: %d\n", dni);
        }
    }
    printf("-----------------------------------------------------\n");

    *cont = *cont + 1;

    if (*cont == 5){
        printf("Pasar a la siguiente pagina.");
        system("pause");
        system("cls");
        *pag = *pag + 1;
        *cont = 0;
        printf("Arbol Binario de Busqueda (preorden)       Pagina: %d\n", *pag);
        printf("-----------------------------------------------------\n");
    }

    preordenABB((*nodo).arbIzq, cont, pag);
    preordenABB((*nodo).arbDer, cont, pag);
}

void mostrarABB(ABB arbol){
    int cont = 0;
    int pag = 1;

    system("cls");
    printf("Arbol Binario de Busqueda (preorden)       Pagina: %d\n", pag);
    printf("-----------------------------------------------------\n");

    preordenABB(arbol.raiz, &cont, &pag);

    printf("Final. ");
    system("pause");
    system("cls");
}


void liberarNodosABB(NodoABB *nodo){
    if (nodo == NULL){
        return;
    }
    liberarNodosABB((*nodo).arbIzq);
    liberarNodosABB((*nodo).arbDer);
    free(nodo);
}

void vaciarABB(ABB *arbol){
    liberarNodosABB((*arbol).raiz);
    initABB(arbol);
}
