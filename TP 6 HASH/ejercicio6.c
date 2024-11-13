#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "tabla_hash.h"
#include "arbol-avl.h"
#include "listas.h"
#include "tipo_elemento.h"
#include "nodo.h"

#define TAMANIO_MAXIMO_TH 2000
#define N_PRIMO 1999

typedef struct {
    int dni;
    char nombre[30];
    char apellido[30];
} personas;

void pedirPersona(personas * p);
int funcionHashModulo(int a);
void cargarEnTablahash(int cantidad_paciente, TablaHash th);
Lista retornar_lista_fecha(TablaHash th, int fecha);
int pedirFecha();
void muestraVacunados(TablaHash th, int fecha);
bool conversionEntero(char *string, int *nro, int len);
void pedirDatos(int *nro, int tamanio);
void leer_palabra(char * c);
void strtrim(char *cadena);

void strtrim(char *cadena) {
    char *comienzoDeCadena = cadena;
    char *finalDeCadena = cadena + strlen(cadena) - 1;
    while (isspace(*comienzoDeCadena)) {
        comienzoDeCadena++;
    }
    while (isspace(*finalDeCadena) && finalDeCadena >= comienzoDeCadena) {
        finalDeCadena--;
    }
    *(finalDeCadena + 1) = '\0';
    memmove(cadena, comienzoDeCadena,   finalDeCadena - comienzoDeCadena + 2);
}

void leer_palabra(char * c) {
    char entrada[30];
    int EsValido = false;

    while (!EsValido){
        int contadorDeEspacios = 0;
        EsValido = true;
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        for (int i=0;i<strlen(entrada);i++){
            if (i != 0 && i != strlen(entrada) && entrada[i] == ' '){
                contadorDeEspacios++;
            } else if (!isalpha(entrada[i]) || contadorDeEspacios > 2){
                EsValido = false;
            }
        }
        if (!EsValido)
            printf("Entrada invalida, Ingrese Nuevamente: ");
    }
    strcpy(c, entrada);
}

bool conversionEntero(char *string, int *nro, int len) {
    int i = 0;
    // Contar la cantidad de espacios.
    while(isspace(string[i]))
        i++;
    // Controlar cadena vacia.
    if (len == i) return false;

    char * buffer = malloc(sizeof(char)*len);
    int indiceEntero = 0;

    // Controlar si es un numero negativo.
    if (string[i] == '-'){
        buffer[indiceEntero] = '-';
        indiceEntero++;
        i++;

        if (!isdigit(string[i])) return false;
    }

    // Leer los digitos.
    while (i < len && !isspace(string[i])){
        if (!isdigit(string[i])) return false;
        buffer[indiceEntero] = string[i];
        indiceEntero++;
        i++;
    }

    // Agregar el caracter nulo al final del string.
    buffer[indiceEntero] = '\0';

    // Termino de recorrer el string.
    while (isspace(string[i]))
        i++;

    // Si hay mas para recorrer y no son blancos, el string contiene otros caracteres.
    if (string[i] != '\0') return false;

    // Convierto el string a un entero.
    *nro = atoi(buffer);

    return true;
}

void pedirDatos(int *nro, int tamanio) {
    bool conversionCorrecta = true;
    do{
        char * bufferNro = malloc(sizeof(char) * tamanio);
        fgets(bufferNro, tamanio, stdin);
        conversionCorrecta = conversionEntero(bufferNro, nro, tamanio);
        if (!conversionCorrecta){
            printf("El numero es invalido, revisa los requerimientos\n");
            printf("Ingrese otro numero: ");
            fflush(stdin);
        }
    } while (!conversionCorrecta);
}

int funcionHashModulo(int a) {
    return (a % N_PRIMO);
}

void cargarEnTablahash(int cantidad_paciente, TablaHash th) {
    int i;
    int anterior = 0;
    int fecha = 0;
    Lista lista_personas;
    TipoElemento valor;
    for (i = 0; i < cantidad_paciente; i++) {
        personas *persona = malloc(sizeof(personas)); // Crear nueva instancia de personas
        fflush(stdin);
        printf(" - - - - Persona %d - - - -\n", i + 1);
        fecha = pedirFecha();
        fflush(stdin);
        pedirPersona(persona);
        lista_personas = retornar_lista_fecha(th,fecha);
        // Verificar si la persona ya está en la lista para esta fecha
        bool existe = false;
        Iterador it = iterador(lista_personas);
        while (hay_siguiente(it)) {
            TipoElemento elem = siguiente(it);
            personas *pExistente = (personas *)elem->valor;
            if (pExistente->dni == persona->dni) {
                existe = true;
                break;
            }
        }

        if (!existe) {
            // Si no existe, agregar a la lista
            l_agregar(lista_personas, te_crear_con_valor(fecha, persona));
            valor = te_crear_con_valor(fecha, lista_personas);
            th_insertar(th, valor);
        } else {
            printf("La persona con DNI %d ya esta registrada en esta fecha.\n", persona->dni);
            free(persona);
        }
        printf("\n");
    }
}

Lista retornar_lista_fecha(TablaHash th, int fecha) {
        if (th_recuperar(th,fecha)){
            Lista lista_fecha = (Lista) th_recuperar(th,fecha)->valor;
        }else{
            Lista lista_fecha_nueva = l_crear();
            return lista_fecha_nueva;
        }
}

void pedirPersona(personas * p) {
    int dni;
    do {
        printf("Ingrese DNI (Max 9 digitos): ");
        pedirDatos(&dni, 11);
        if (dni < 1 || dni > 999999999)
            printf("Valor fuera de rango.\n");
    } while (dni < 1 || dni > 999999999);
    p -> dni = dni;
    fflush(stdin);
    printf("Ingrese Nombre (Se permiten hasta 2 espacios): ");
    leer_palabra(p -> nombre);
    printf("Ingrese Apellido (Se permiten hasta 2 espacios): ");
    leer_palabra(p -> apellido);
}

int pedirFecha() {
    int fechaTotal = 0;
    int dia, mes, anio;
    bool fechaValida;
    do {
        fechaValida = true;
        do {
        printf("Ingrese Dia de Vacunacion (Hasta 2 digitos): ");
        pedirDatos(&dia, 11);
        if (dia < 1 || dia > 31)
            printf("Entrada Invalida.\n");
        } while (dia < 1 || dia > 31);

        do {
            printf("Ingrese Mes de Vacunacion (Hasta 2 digitos): ");
            pedirDatos(&mes, 11);
            if (mes < 1 || mes > 12)
                printf("Entrada Invalida.\n");
        } while (mes < 1 || mes > 12);

        do {
            printf("Ingrese Anio de Vacunacion (4 digitos, desde 2020 hasta 2024): ");
            pedirDatos(&anio, 11);
            if (anio < 2020 || anio > 2024)
                printf("Entrada Invalida.\n");
        } while (anio < 2020 || anio > 2024);

        //Se valida anio bisiesto (Sucede en 2020)
        if ((((mes == 2 && (dia > 29 || (dia > 28 && !((anio % 4 == 0) && (anio % 100 != 0 || anio % 400 == 0))))) ||
        ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)))){
            printf("Fecha Invalida.\n");
            fechaValida = false;
        }

        //Se valida fecha maxima.
        if (anio == 2024){
            if (mes >= 6 && dia > 6){ //Se permite fecha hasta el dia de entrega del TP.
                printf("Fecha Invalida.\n");
                fechaValida = false;
            }
        }

    } while (!fechaValida);

    fechaTotal = (dia * 1000000) + (mes * 10000) + anio;
    return fechaTotal;
}

void muestraVacunados(TablaHash th, int fecha) {
    if (th_recuperar(th, fecha)){
        Lista Muestro = (Lista)th_recuperar(th, fecha)->valor;
        Iterador ite = iterador(Muestro);
        TipoElemento X;
        while (hay_siguiente(ite)) {
            X = siguiente(ite);
            personas per = *(personas *)X->valor;
            printf("- - - - - - - - - - \n");
            printf("\nDNI: %d\n", per.dni);
            printf("Apellido: %s\n", per.apellido);
            printf("Nombre: %s\n", per.nombre);
            printf("- - - - - - - - - - \n");
        }
    } else {
        printf("No hay personas vacunadas en esa fecha.\n");
    }
}

int main() {
    TablaHash th = th_crear(TAMANIO_MAXIMO_TH, &funcionHashModulo);
    int menu = -1;
    while (menu != 0){
        int opcionMenu;
        do {
            printf("- - - - CONSULTA DE VACUNACION - - - -\n");
            printf(" 0. Salir del programa \n");
            printf(" 1. Registrar Vacunados \n");
            printf(" 2. Ver Vacunados por fecha \n");
            printf(" Ingrese la opcion deseada: ");
            fflush(stdin);
            pedirDatos(&opcionMenu, 11);
            if (opcionMenu < 0 || opcionMenu > 2){
                printf("Valor fuera del rango de opciones, pulse una tecla\n");
                system("pause");
                system("cls");

            }
        } while (opcionMenu < 0 || opcionMenu > 2);

        if (opcionMenu == 1){
            int cantidadDeVacunados;
            printf("Ingrese la cantidad de vacunados a registrar: ");
            pedirDatos(&cantidadDeVacunados, 11);
            cargarEnTablahash(cantidadDeVacunados,th);
        } else if (opcionMenu == 2){
            printf("- - - Fecha a consultar vacunados - - - \n");
            int fecha = pedirFecha();
            muestraVacunados(th, fecha);
        } else {
            printf("Gracias por utilizar el programa!\n");
            menu = 0;
        }
    system("pause");
    system("cls");
    }
    return 0;
}
