#include <stdio.h>
#include "LSOBB.h"
#include "LVO.h"
#include "ABB.h"

//Grupo 15
// Integrantes: Lorenzo Luna y Santino Capdevila
//
// Conclusion:
// Luego de analizar y ejecutar pruebas sobre las tres estructuras, podemos afirmar
// que, para las operaciones y los datos utilizados, el ABB resulta la
// alternativa mas conveniente debido al equilibrio entre los costos de alta,
// baja y evocacion.
//
// Nuestra conclusion depende del orden de insercion. Si los DNI se
// dan de alta de forma creciente o decreciente, el ABB puede degenerarse y las
// operaciones que requieren localizar pasan de tener un comportamiento cercano
// de O(log N) a O(N), como una LVO.
//
// Por lo tanto, el ABB ofrece buenos resultados en este caso particular, pero
// su eficiencia depende de que el arbol no quede excesivamente desbalanceado.
//
//
// Resultados de la comparacion (archivo Pruebas.txt, 8975 operaciones):
// Operaciones procesadas: 8975
//
// --- Costos LSOBB ---
// Alta exitosa: cantidad 2746, maximo 2000.00, promedio 413.65
// Baja exitosa: cantidad 2001, maximo 2000.00, promedio 503.36
// Evocacion exitosa: cantidad 2175, maximo 11.00, promedio 10.14
// Evocacion fracasada: cantidad 2053, maximo 11.00, promedio 9.88
//
// --- Costos LVO ---
// Alta exitosa: cantidad 2746, maximo 1.00, promedio 1.00
// Baja exitosa: cantidad 2001, maximo 0.50, promedio 0.50
// Evocacion exitosa: cantidad 2175, maximo 1994.00, promedio 566.80
// Evocacion fracasada: cantidad 2053, maximo 1206.00, promedio 463.47
//
// --- Costos ABB ---
// Alta exitosa: cantidad 2746, maximo 0.50, promedio 0.50
// Baja exitosa: cantidad 2001, maximo 1.50, promedio 1.02
// Evocacion exitosa: cantidad 2175, maximo 22.00, promedio 11.84
// Evocacion fracasada: cantidad 2053, maximo 21.00, promedio 12.03

typedef struct {
    int cantidad;
    double sumaCostos;
    double maximo;
} Estadistica_Costos;



void leer_elector(FILE *archivo, Elector *elector, int *exito){
    int leidos;
    int dni, codigoPostal, mesa, circuito;
    char nombreApellido[51];
    char domicilio[81];

    leidos = fscanf(archivo,
                    "%d\n%50[^\r\n]\n%80[^\r\n]\n%d\n%d\n%d\n",
                    &dni,
                    nombreApellido,
                    domicilio,
                    &codigoPostal,
                    &mesa,
                    &circuito);

    *exito = (leidos == 6);
    if (*exito == 1){
        setDni(elector, dni);
        setNombreApellido(elector, nombreApellido);
        setDomicilio(elector, domicilio);
        setCodigoPostal(elector, codigoPostal);
        setMesa(elector, mesa);
        setCircuito(elector, circuito);
    }
}



void ActualizarEstadistica(Estadistica_Costos *estadistica, double costo){
    (*estadistica).cantidad++;
    (*estadistica).sumaCostos += costo;

    if (costo > (*estadistica).maximo){
        (*estadistica).maximo = costo;
    }
}



void MostrarEstadistica(char *nombre, Estadistica_Costos estadistica){
    double promedio;

    if (estadistica.cantidad == 0){
        printf("%s: no hubo operaciones.\n", nombre);
        return;
    }

    promedio = estadistica.sumaCostos / estadistica.cantidad;
    printf("%s: cantidad %d, maximo %.2f, promedio %.2f\n",
           nombre, estadistica.cantidad, estadistica.maximo, promedio);
}



void CompararEstructuras(LSOBB *lso, LVO *lvo, ABB *abb){
    FILE *archivo;
    char linea[128];
    int codigo;
    int dni;
    int lecturaExitosa;
    int operaciones = 0;
    Elector elector;
    Elector resultadoLso, resultadoLvo, resultadoAbb;

    int exitoLso, exitoLvo, exitoAbb;
    int costoLso;
    int costoEvocacionLvo, costoEvocacionAbb;
    double costoLvo, costoAbb;

    Estadistica_Costos altaLso = {0};
    Estadistica_Costos bajaLso = {0};
    Estadistica_Costos evocacionExitosaLso = {0};
    Estadistica_Costos evocacionFracasadaLso = {0};

    Estadistica_Costos altaLvo = {0};
    Estadistica_Costos bajaLvo = {0};
    Estadistica_Costos evocacionExitosaLvo = {0};
    Estadistica_Costos evocacionFracasadaLvo = {0};

    Estadistica_Costos altaAbb = {0};
    Estadistica_Costos bajaAbb = {0};
    Estadistica_Costos evocacionExitosaAbb = {0};
    Estadistica_Costos evocacionFracasadaAbb = {0};

    archivo = fopen("Operaciones_Padron.txt", "r");
    if (archivo == NULL){
        printf("No se pudo abrir Operaciones_Padron.txt.\n");
        return;
    }

    
    init_Lso(lso);
    vaciarLVO(lvo);
    vaciarABB(abb);

    while (fgets(linea, sizeof(linea), archivo) != NULL){
        if (sscanf(linea, "%d", &codigo) != 1){
            printf("Codigo de operacion invalido.\n");
            fclose(archivo);
            return;
        }

       
        if (codigo == 1 || codigo == 2){
            leer_elector(archivo, &elector, &lecturaExitosa);
            if (lecturaExitosa == 0){
                printf("No se pudo leer el elector completo.\n");
                fclose(archivo);
                return;
            }
        }

        if (codigo == 1){
            Alta_Lso(lso, elector, &exitoLso, &costoLso);
            AltaLVO(lvo, elector, &exitoLvo, &costoLvo);
            AltaABB(abb, elector, &exitoAbb, &costoAbb);

            if (exitoLso == -1 || exitoLvo == -1 || exitoAbb == -1){
                printf("Comparacion interrumpida: falta espacio o memoria para un alta.\n");
                fclose(archivo);
                return;
            }

            if (exitoLso == 1){
                ActualizarEstadistica(&altaLso, costoLso);
            }
            if (exitoLvo == 1){
                ActualizarEstadistica(&altaLvo, costoLvo);
            }
            if (exitoAbb == 1){
                ActualizarEstadistica(&altaAbb, costoAbb);
            }
        }
        else if (codigo == 2){
            Baja_Lso(lso, elector, &exitoLso, &costoLso);
            BajaLVO(lvo, elector, &exitoLvo, &costoLvo);
            BajaABB(abb, elector, &exitoAbb, &costoAbb);

            if (exitoLso == 1){
                ActualizarEstadistica(&bajaLso, costoLso);
            }
            if (exitoLvo == 1){
                ActualizarEstadistica(&bajaLvo, costoLvo);
            }
            if (exitoAbb == 1){
                ActualizarEstadistica(&bajaAbb, costoAbb);
            }
        }
        else if (codigo == 3){
            if (fgets(linea, sizeof(linea), archivo) == NULL){
                printf("Falta el DNI de la evocacion.\n");
                fclose(archivo);
                return;
            }
            if (sscanf(linea, "%d", &dni) != 1){
                printf("DNI de evocacion invalido.\n");
                fclose(archivo);
                return;
            }

            Evocacion_Lso(lso, dni, &resultadoLso, &exitoLso, &costoLso);
            EvocacionLVO(lvo, dni, &resultadoLvo, &exitoLvo, &costoEvocacionLvo);
            EvocacionABB(abb, dni, &resultadoAbb, &exitoAbb, &costoEvocacionAbb);

            if (exitoLso == 1){
                ActualizarEstadistica(&evocacionExitosaLso, costoLso);
            }else{
                ActualizarEstadistica(&evocacionFracasadaLso, costoLso);
            }
            if (exitoLvo == 1){
                ActualizarEstadistica(&evocacionExitosaLvo, costoEvocacionLvo);
            }else{
                ActualizarEstadistica(&evocacionFracasadaLvo, costoEvocacionLvo);
            }
            if (exitoAbb == 1){
                ActualizarEstadistica(&evocacionExitosaAbb, costoEvocacionAbb);
            }else{
                ActualizarEstadistica(&evocacionFracasadaAbb, costoEvocacionAbb);
            }
        }
        else{
            printf("Codigo de operacion desconocido: %d\n", codigo);
            fclose(archivo);
            return;
        }

        operaciones++;
    }

    fclose(archivo);

    printf("\nOperaciones procesadas: %d\n", operaciones);

    printf("\n--- Costos LSOBB ---\n");
    MostrarEstadistica("Alta exitosa", altaLso);
    MostrarEstadistica("Baja exitosa", bajaLso);
    MostrarEstadistica("Evocacion exitosa", evocacionExitosaLso);
    MostrarEstadistica("Evocacion fracasada", evocacionFracasadaLso);

    printf("\n--- Costos LVO ---\n");
    MostrarEstadistica("Alta exitosa", altaLvo);
    MostrarEstadistica("Baja exitosa", bajaLvo);
    MostrarEstadistica("Evocacion exitosa", evocacionExitosaLvo);
    MostrarEstadistica("Evocacion fracasada", evocacionFracasadaLvo);

    printf("\n--- Costos ABB ---\n");
    MostrarEstadistica("Alta exitosa", altaAbb);
    MostrarEstadistica("Baja exitosa", bajaAbb);
    MostrarEstadistica("Evocacion exitosa", evocacionExitosaAbb);
    MostrarEstadistica("Evocacion fracasada", evocacionFracasadaAbb);
}


void MenuMostrar(LSOBB *lso, LVO *lvo, ABB *abb){
    int opcion = -1;

    while (opcion != 0){
        printf("\n--- Mostrar estructuras ---\n");
        printf("1. LVO\n");
        printf("2. LSOBB\n");
        printf("3. ABB\n");
        printf("0. Volver al menu principal\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1){
            printf("Debes ingresar un numero.\n");
            return;
        }

        switch (opcion){
            case 1:
                mostrarLVO(*lvo);
                break;
            case 2:
                Mostrar_Lso(lso);
                break;
            case 3:
                mostrarABB(*abb);
                break;
            case 0:
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    }
}


int main(void){
    LSOBB lso;
    LVO lvo = {0};
    ABB abb;
    int opcion = -1;

    init_Lso(&lso);
    initLVO(&lvo);
    initABB(&abb);

    if (lvo.acc == NULL){
        printf("No se pudo reservar memoria para la LVO.\n");
        return 1;
    }

        while (opcion != 0){
        printf("\n--- Padron electoral ---\n");
        printf("1. Comparar estructuras\n");
        printf("2. Mostrar estructuras\n");
        printf("0. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1){
            printf("Debes ingresar un numero.\n");
            break;
        }

        switch (opcion){
            case 1:
                CompararEstructuras(&lso, &lvo, &abb);
                break;
            case 2:
                MenuMostrar(&lso, &lvo, &abb);
                break;
            case 0:
                printf("Fin del programa.\n");
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    }

    liberarLVO(&lvo);
    vaciarABB(&abb);
    return 0;
}



