#include "LSOBB.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_Lso(LSOBB *lista)
{
    (*lista).cantidad = 0;
}

int isEmpty_Lso(LSOBB *lista)
{
    return (*lista).cantidad == 0;
}

int isfull_Lso(LSOBB *lista)
{
    return (*lista).cantidad == Max_Electores;
}

void Localizar_Lso(LSOBB *lista, int dni, int *pos, int *exito, int *costo)
{
    int li = 0;
    int ls = (*lista).cantidad - 1;
    int medio;
    int dniActual;
    int consultadas[Max_Electores] = {0};

    *pos = 0;
    *exito = 0;
    *costo = 0;

    if (isEmpty_Lso(lista))
    {
        return;
    }

    while (li < ls)
    {
        medio = (li + ls) / 2;
        if (consultadas[medio] == 0)
        {
            *costo = *costo + 1;
            consultadas[medio] = 1;
        }
        getDni(&(*lista).Dato[medio], &dniActual);
        if (dni <= dniActual)
        {
            ls = medio;
        }
        else
        {
            li = medio + 1;
        }
    }

    if (consultadas[li] == 0)
    {
        *costo = *costo + 1;
        consultadas[li] = 1;
    }
    
    *pos = li;
    getDni(&(*lista).Dato[li], &dniActual);
    *exito = (dniActual == dni);

    if (dniActual < dni)
    {
        *pos = li + 1;
    }

    
}


void Alta_Lso(LSOBB *lista, Elector nuevo, int *exito, int *costo)
{
    int pos;
    int encontrado;
    int dni;
    int costoBusqueda;
    int i;

    *exito = 0;
    *costo = 0;
    getDni(&nuevo, &dni);
    Localizar_Lso(lista, dni, &pos, &encontrado, &costoBusqueda);

    if (encontrado == 1)
    {
        return;
    }

    if (isfull_Lso(lista))
    {
        *exito = -1;
        return;
    }
    for (i = (*lista).cantidad; i > pos; i--)
    {
        (*lista).Dato[i] = (*lista).Dato[i - 1];
        *costo = *costo + 1;
    }

    (*lista).Dato[pos] = nuevo;
    (*lista).cantidad++;
    *exito = 1;
}

void Baja_Lso(LSOBB *lista, Elector elector, int *exito, int *costo)
{
    int pos;
    int encontrado;
    int dni;
    int costoBusqueda;
    int coinciden;
    char nombreApellidoGuardado[51], nombreApellidoBorrar[51];
    char domicilioGuardado[81], domicilioBorrar[81];
    int codigoPostalGuardado, codigoPostalBorrar;
    int mesaGuardado, mesaBorrar;
    int circuitoGuardado, circuitoBorrar;
    int i;

    *exito = 0;
    *costo = 0;
    getDni(&elector, &dni);
    Localizar_Lso(lista, dni, &pos, &encontrado, &costoBusqueda);

    if (encontrado == 0)
    {
        return;
    }

    getNombreApellido(&((*lista).Dato[pos]), nombreApellidoGuardado);
    getNombreApellido(&elector, nombreApellidoBorrar);
    getDomicilio(&((*lista).Dato[pos]), domicilioGuardado);
    getDomicilio(&elector, domicilioBorrar);
    getCodigoPostal(&((*lista).Dato[pos]), &codigoPostalGuardado);
    getCodigoPostal(&elector, &codigoPostalBorrar);
    getMesa(&((*lista).Dato[pos]), &mesaGuardado);
    getMesa(&elector, &mesaBorrar);
    getCircuito(&((*lista).Dato[pos]), &circuitoGuardado);
    getCircuito(&elector, &circuitoBorrar);

    coinciden = stricmp(nombreApellidoGuardado, nombreApellidoBorrar) == 0 &&
                stricmp(domicilioGuardado, domicilioBorrar) == 0 &&
                codigoPostalGuardado == codigoPostalBorrar &&
                mesaGuardado == mesaBorrar &&
                circuitoGuardado == circuitoBorrar;

    if (coinciden == 0)
    {
        return;
    }

    for (i = pos; i < (*lista).cantidad - 1; i++)
    {
        (*lista).Dato[i] = (*lista).Dato[i + 1];
        *costo = *costo + 1;
    }

    (*lista).cantidad--;
    *exito = 1;
}

void Mostrar_Lso(LSOBB *lista)
{
    int dni;
    char nombreApellido[51];
    char domicilio[81];
    int codigoPostal;
    int mesa;
    int circuito;
    int cont = 0;
    int pag = 1;
    int i;

    system("cls");
    printf("Lista Secuencial Ordenada                  Pagina: %d\n", pag);
    printf("-----------------------------------------------------\n");

    for (i = 0; i < (*lista).cantidad; i++)
    {
        getDni(&((*lista).Dato[i]), &dni);
        getNombreApellido(&((*lista).Dato[i]), nombreApellido);
        getDomicilio(&((*lista).Dato[i]), domicilio);
        getCodigoPostal(&((*lista).Dato[i]), &codigoPostal);
        getMesa(&((*lista).Dato[i]), &mesa);
        getCircuito(&((*lista).Dato[i]), &circuito);

        printf("Nombre: %s\n", nombreApellido);
        printf("DNI: %d\n", dni);
        printf("Domicilio: %s\n", domicilio);
        printf("Codigo Postal: %d\n", codigoPostal);
        printf("Mesa: %d\n", mesa);
        printf("Circuito: %d\n", circuito);
        printf("-----------------------------------------------------\n");

        cont = cont + 1;

        if (cont == 10 && i + 1 < (*lista).cantidad)
        {
            printf("Pasar a la siguiente pagina.");
            system("pause");
            system("cls");
            pag = pag + 1;
            cont = 0;
            printf("Lista Secuencial Ordenada                  Pagina: %d\n", pag);
            printf("-----------------------------------------------------\n");
        }
    }

    printf("Final. ");
    system("pause");
    system("cls");
}

void Evocacion_Lso(LSOBB *lista,int dni,Elector *Electo,int *exito,int *costo)
{
    int pos;
    Localizar_Lso(lista,dni,&pos,exito,costo);
    if (*exito == 0)
    {
        return;
    }
    *Electo = (*lista).Dato[pos];
}
