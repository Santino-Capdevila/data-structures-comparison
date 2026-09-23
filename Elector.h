#ifndef ELECTOR_H
#define ELECTOR_H

typedef struct
{
    int dni;
    char nombreApellido[51];
    char domicilio[81];
    int codigoPostal;
    int mesa;
    int circuito;
} Elector;

/* Los buffers de salida deben tener 51 caracteres para nombre y 81 para domicilio. */
void setDni(Elector *elector, int dni);
void getDni(const Elector *elector, int *dni);

void setNombreApellido(Elector *elector, const char *nombreApellido);
void getNombreApellido(const Elector *elector, char *nombreApellido);

void setDomicilio(Elector *elector, const char *domicilio);
void getDomicilio(const Elector *elector, char *domicilio);

void setCodigoPostal(Elector *elector, int codigoPostal);
void getCodigoPostal(const Elector *elector, int *codigoPostal);

void setMesa(Elector *elector, int mesa);
void getMesa(const Elector *elector, int *mesa);

void setCircuito(Elector *elector, int circuito);
void getCircuito(const Elector *elector, int *circuito);

#endif
