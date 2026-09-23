#include "Elector.h"
#include <string.h>

void setDni(Elector *elector, int dni){
    (*elector).dni = dni;
}

void getDni(const Elector *elector, int *dni){
    *dni = (*elector).dni;
}

void setNombreApellido(Elector *elector, const char *nombreApellido){
    strncpy((*elector).nombreApellido, nombreApellido, 50);
    (*elector).nombreApellido[50] = '\0';
}

void getNombreApellido(const Elector *elector, char *nombreApellido){
    strcpy(nombreApellido, (*elector).nombreApellido);
}

void setDomicilio(Elector *elector, const char *domicilio){
    strncpy((*elector).domicilio, domicilio, 80);
    (*elector).domicilio[80] = '\0';
}

void getDomicilio(const Elector *elector, char *domicilio){
    strcpy(domicilio, (*elector).domicilio);
}

void setCodigoPostal(Elector *elector, int codigoPostal){
    (*elector).codigoPostal = codigoPostal;
}

void getCodigoPostal(const Elector *elector, int *codigoPostal){
    *codigoPostal = (*elector).codigoPostal;
}

void setMesa(Elector *elector, int mesa){
    (*elector).mesa = mesa;
}

void getMesa(const Elector *elector, int *mesa){
    *mesa = (*elector).mesa;
}

void setCircuito(Elector *elector, int circuito){
    (*elector).circuito = circuito;
}

void getCircuito(const Elector *elector, int *circuito){
    *circuito = (*elector).circuito;
}
