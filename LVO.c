#include "LVO.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void initLVO(LVO *lista){
    NodoLVO *nuevo = (NodoLVO*)malloc(sizeof(NodoLVO));
    if (nuevo == NULL){
        return;
    }
    setDni(&(*nuevo).dato, INFINITO);
    (*lista).acc = nuevo;
    (*(*lista).acc).sig = NULL;
    (*lista).aux = (*lista).acc;
    (*lista).cur = (*lista).acc;
}


void forwardLVO(LVO *lista){
    if ((*lista).cur != NULL){
        (*lista).aux = (*lista).cur;
        (*lista).cur = (*(*lista).cur).sig;
    }
}

void vaciarLVO(LVO *lista){
    NodoLVO *borrar;
    int dni;

    while ((*lista).acc != NULL){
        getDni(&(*(*lista).acc).dato, &dni);
        if (dni == INFINITO){
            break;
        }
        borrar = (*lista).acc;
        (*lista).acc = (*borrar).sig;
        free(borrar);
    }
    (*lista).cur = (*lista).acc;
    (*lista).aux = (*lista).acc;
}

void liberarLVO(LVO *lista){
    vaciarLVO(lista);
    free((*lista).acc);
    (*lista).acc = NULL;
    (*lista).cur = NULL;
    (*lista).aux = NULL;
}

void insertLVO(LVO *lista, Elector nuevoDato, int *exito, double *costo){
    NodoLVO *nuevo = (NodoLVO*)malloc(sizeof(NodoLVO));
    *exito = -1;
    *costo = 0;
    if (nuevo == NULL)
    {
        return;
    }
    (*nuevo).dato = nuevoDato;

    if ((*lista).cur == (*lista).acc)
    {
        (*nuevo).sig = (*lista).acc;
        *costo = *costo + 0.5;
        (*lista).acc = nuevo;
        *costo = *costo + 0.5;
        (*lista).aux = nuevo;
        (*lista).cur = nuevo;
        *exito = 1;
        return;
    }
    else
    {
        (*nuevo).sig = (*lista).cur;
        *costo = *costo + 0.5;
        (*(*lista).aux).sig = nuevo;
        *costo = *costo + 0.5;
        (*lista).cur = nuevo;
        *exito = 1;
    }
}

void supressLVO(LVO *lista, double *costo){
    *costo = 0;
    if ((*lista).acc == (*lista).cur)
    {
        (*lista).acc = (*(*lista).aux).sig;
        *costo = *costo + 0.5;
        (*lista).aux = (*(*lista).aux).sig;
        free((*lista).cur);
        (*lista).cur = (*lista).aux;
    }
    else
    {
        (*(*lista).aux).sig = (*(*lista).cur).sig;
        *costo = *costo + 0.5;
        free((*lista).cur);
        (*lista).cur = (*(*lista).aux).sig;
    }
}

void copyLVO(LVO *lista, Elector *electo){
    *electo = (*(*lista).cur).dato;
}

void resetLVO(LVO *lista){
    (*lista).cur = (*lista).acc;
    (*lista).aux = (*lista).acc;
}

void LocalizarLVO(LVO *lista, int dni, int *exito, int *costo){
    int dniActual;
    *exito = 0;
    *costo = 0;
    resetLVO(lista);
    *costo = *costo + 1;
    getDni(&(*(*lista).cur).dato, &dniActual);
    while(dniActual != INFINITO && dniActual < dni){
        forwardLVO(lista);
        getDni(&(*(*lista).cur).dato, &dniActual);
        *costo = *costo + 1;
    }
    *exito = (dniActual != INFINITO &&
              dniActual == dni);
}

void AltaLVO(LVO *lista, Elector nuevo, int *exito, double *costo){
    int encontrado;
    int dni;
    int costoBusqueda;

    *exito = 0;
    *costo = 0;
    getDni(&nuevo, &dni);
    LocalizarLVO(lista, dni, &encontrado, &costoBusqueda);

    if (encontrado == 1){
        return;
    }

    insertLVO(lista, nuevo, exito, costo);
}

void BajaLVO(LVO *lista, Elector borrar, int *exito, double *costo){
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
    LocalizarLVO(lista, dni, &encontrado, &costoBusqueda);

    if (encontrado == 0){
        return;
    }

    getNombreApellido(&((*(*lista).cur).dato), nombreApellidoGuardado);
    getNombreApellido(&borrar, nombreApellidoBorrar);
    getDomicilio(&((*(*lista).cur).dato), domicilioGuardado);
    getDomicilio(&borrar, domicilioBorrar);
    getCodigoPostal(&((*(*lista).cur).dato), &codigoPostalGuardado);
    getCodigoPostal(&borrar, &codigoPostalBorrar);
    getMesa(&((*(*lista).cur).dato), &mesaGuardado);
    getMesa(&borrar, &mesaBorrar);
    getCircuito(&((*(*lista).cur).dato), &circuitoGuardado);
    getCircuito(&borrar, &circuitoBorrar);

    coinciden = stricmp(nombreApellidoGuardado, nombreApellidoBorrar) == 0 &&
                stricmp(domicilioGuardado, domicilioBorrar) == 0 &&
                codigoPostalGuardado == codigoPostalBorrar &&
                mesaGuardado == mesaBorrar &&
                circuitoGuardado == circuitoBorrar;

    if (coinciden == 0){
        return;
    }

    supressLVO(lista, costo);
    *exito = 1;
}

void EvocacionLVO(LVO *lista, int dni, Elector *electo, int *exito, int *costo){
    LocalizarLVO(lista, dni, exito, costo);
    if (*exito == 0){
        return;
    }
    copyLVO(lista, electo);
}

void mostrarLVO(LVO lista){
    int dni;
    char nombreApellido[51];
    char domicilio[81];
    int codigoPostal;
    int mesa;
    int circuito;
    int cont = 0;
    int pag = 1;

    lista.cur = lista.acc;

    system("cls");
    printf("Lista Vinculada Ordenada                   Pagina: %d\n", pag);
    printf("-----------------------------------------------------\n");

    getDni(&(*lista.cur).dato, &dni);
    while (dni != INFINITO){
        getNombreApellido(&((*lista.cur).dato), nombreApellido);
        getDomicilio(&((*lista.cur).dato), domicilio);
        getCodigoPostal(&((*lista.cur).dato), &codigoPostal);
        getMesa(&((*lista.cur).dato), &mesa);
        getCircuito(&((*lista.cur).dato), &circuito);

        printf("Nombre: %s\n", nombreApellido);
        printf("DNI: %d\n", dni);
        printf("Domicilio: %s\n", domicilio);
        printf("Codigo Postal: %d\n", codigoPostal);
        printf("Mesa: %d\n", mesa);
        printf("Circuito: %d\n", circuito);
        printf("-----------------------------------------------------\n");

        cont = cont + 1;
        lista.cur = (*lista.cur).sig;
        getDni(&(*lista.cur).dato, &dni);

        if (cont == 10 && dni != INFINITO){
            printf("Pasar a la siguiente pagina.");
            system("pause");
            system("cls");
            pag = pag + 1;
            cont = 0;
            printf("Lista Vinculada Ordenada                   Pagina: %d\n", pag);
            printf("-----------------------------------------------------\n");
        }
    }

    printf("Final. ");
    system("pause");
    system("cls");
}
