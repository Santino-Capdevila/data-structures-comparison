#ifndef LSOBB_H
#define LSOBB_H
#include "Elector.h"
#define Max_Electores 2500

typedef struct LSOBB{
Elector Dato[Max_Electores];
int cantidad;
}LSOBB;


void init_Lso(LSOBB *lista);
int isEmpty_Lso(LSOBB *lista);
int isfull_Lso(LSOBB *lista);
//Funciones
void Localizar_Lso(LSOBB *lista, int dni, int *pos, int *exito, int *costo);
void Alta_Lso(LSOBB *lista, Elector nuevo, int *exito, int *costo);
void Baja_Lso(LSOBB *lista, Elector elector, int *exito, int *costo);
void Mostrar_Lso(LSOBB *lista);
void Evocacion_Lso(LSOBB *lista, int dni, Elector *Electo, int *exito, int *costo);

#endif 
