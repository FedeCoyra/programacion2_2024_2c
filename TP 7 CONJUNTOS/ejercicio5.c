#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "conjuntos.h"
#include "listas.h"
#include "tipo_elemento.h"
#include "arbol-avl.h"
#include "nodo.h"

#define TAMANO_NUM 15


// ================== VALIDACIONES ==================

// funcion que valida que un numero entero sea ingresado por teclado
bool esEntero(char numIngresado[]) {
    int verificacionNumero = 0;
    bool flag = true;
    int posicion = 0;
    int cantNum = 0;

    while (cantNum < strlen(numIngresado) - 1 && flag) {
        if ((numIngresado[posicion] == '-') && (posicion == 0)) {
            if (strlen(numIngresado)-1 == 1) {
                printf("\nEl dato ingresado por teclado no es un numero.\n");
                flag = false;
            }
            posicion ++;
            cantNum ++;
        }
        else if (numIngresado[posicion] == ' ') {
            printf("\nNo se admiten los espacios en blanco.\n");
            flag = false;
        }
        else if (numIngresado[posicion] == '\0' && (cantNum == strlen(numIngresado))) {
            posicion++;
            cantNum ++;
        }
        else {
            verificacionNumero = isdigit(numIngresado[posicion]);
            if (verificacionNumero != 0) {
                posicion++;
                cantNum ++;
            } else {
                printf("\nEl dato ingresado por teclado no es un numero.\n");
                flag = false;
            }
        }
    }
    return flag;
}

// funcion que valida si un numero es 0
bool numeroEsCero(int numero) {
    bool flag = true;
    if (numero == 0) {
        printf("\nNo se puede introducir un '0'.\n");
        flag = false;
    }
    return flag;
}

// funcion que valida la cantidad de caracteres de una cadena
bool cantidadDeCaracteres(char cadena[], int limite) {
    bool estado = true;
    if (strlen(cadena) > limite) {
        printf("\nLa cadena de texto ingresada es demasiado grande.\n");
        estado = false;
    }
    return estado;
}

// funcion que convierte un array de chars a integer
int convertirChar(char numIngresado[]) {
    int numero;
    numero = atoi(numIngresado);
    return numero;
}

// funcion que verifica si el primer caracter es un \n
bool esEnter(char cadena[]) {
    bool flag = true;
    if ((cadena[0] == '\n' || cadena[0]== '\0')) {
        printf("\nEl dato ingresado no es valido.\n");
        flag = false;
    }
    return flag;
}

// funcion que verifia si el primer caracter (punteros) es un \n
bool esEnterPuntero(char *cadena) {
    bool flag = true;
    if (*cadena == '\n' || *cadena== '\0') {
        printf("\nEl dato ingresado no es valido.\n");
        flag = false;
    }
    return flag;
}

// funcion que valida que el numero este dentro del rango especificado
bool numeroRango(int numero, int limInf, int limSup) {
    bool flag = true;
    if (numero < limInf || numero > limSup){
        printf("\nEl dato ingresado esta fuera de rango.\nEl intervalo permitido es [%d,%d].\n", limInf, limSup);
        flag = false;
    }
    return flag;
}

bool numeroRangoMedio(int numero, int infMax, int infMin, int supMin, int supMax) {
    bool flag = true;
    if ((numero > infMin && numero < supMin) || numero > supMax  ||  numero < infMax) {
        printf("\nEl dato ingresado esta fuera de rango.\nEl intervalo permitido es [%d,%d]...[%d,%d].\n", infMax, infMin, supMin, supMax);
        flag = false;
    }
    return flag;
}

// funcion que transforma cada caracter en su version a minuscula
void toLower(char cadena[]) {
    int i;
    for (i = 0; i < strlen(cadena); i++) {
        cadena[i] = tolower(cadena[i]);
    }
}

// funcion que compara todos los caracteres de una cadena con dos que recibimos por parametro
bool comparaCaracteres(char cadena[], char caracter_1, char caracter_2) {
    bool flag = true;
    int i = 0;
    while (i < strlen(cadena) && flag) {
        char caracter = cadena[i];
        if ((caracter != caracter_1) && (caracter != caracter_2)) {
            printf("\nLa cadena ingresada no es valida.\nSolo se admiten '%c/%c' o '%c/%c'.\n",toupper(caracter_1),caracter_1,toupper(caracter_2),caracter_2);
            flag = false;
        }
        i++;
    }
    return flag;
}

// funcion que trunca los 0 a la izquierda que tenga la cadena ingresada y retorna el numero
char *truncarCeros (char *dato) {
    //control de ceros a la izquierda
    while (*dato == '0') { // Comparamos el primer elemento del arreglo con el carácter '0'
        if (strlen(dato) > 1) { //verificamos que la cadena no esté vacía y que tenga un elemento siguiente donde truncar
            char * auxiliar = malloc(sizeof(char) * (strlen(dato)));
            strncpy(auxiliar, dato + 1, strlen(dato));
            dato = auxiliar;
        }
        else if (strlen(dato) == 1) { //si la cadena queda como un unico 0, lo retornamos para no destruir la cadena
            return dato;
        }
    }
    return dato;
}

// funcion que inserta el "-" que se elimino previamente para los numeros negativos ingresados
char *insertarMenos (char * dato) {
    char* guion = "-";
    char* auxiliar = malloc(sizeof(char) * strlen(dato) + 2);
    strcpy(auxiliar, guion);
    strcat(auxiliar,dato);
    return auxiliar;
}

// funcion que trunca el signo negativo al numero ingresado
char *truncarMenos (char *dato) {
    char * auxiliar = malloc(sizeof(char) * (strlen(dato)));
    strncpy(auxiliar, dato + 1, strlen(dato));
    dato = auxiliar;
    return dato;
}

// funcion que retorna true en caso que la cadena ingresada corresponda a un numero negativo
bool controlMenos (char *numero) {
    if (*numero == '-') {
        return true;
    }
    else{
        return false;
    }
}

// funcion que verifica si el caracter es nulo
bool esUnNulo (char caracterIngresado[]) {
    if (strlen(caracterIngresado)-1 == 1) {
        if (caracterIngresado[0] == '.') return true;
        else return false;
    } else return false;
}

// funcion que chequea que todos los caracteres sean letras
bool soloLetras(const char* cadena) {
    while (*cadena) {
        if (!isalpha(*cadena) && !isspace(*cadena)) {
            printf("\nEl dato ingresado por teclado no es correcto.\n");
            return false;
        }
        cadena++;
    }
    return true;
}

// funcion que chequea que todos los caracteres sean numeros
bool soloNumeros(const char* cadena) {
    while (*cadena) {
        if (!isdigit(*cadena) && !isspace(*cadena)) {
            printf("\nEl dato ingresado por teclado no corresponde a un numero.\n");
            return false;
        }
        cadena++;
    }
    return true;
}

// ================== ENTRADAS ==================

// funciones que cargan un conjunto
void cargarConjunto(Conjunto c) {
    bool entrada = true;
    char num[TAMANO_NUM];
    int cantidadElementos, opcion, numero, i = 0;
    TipoElemento elemento;

    printf("\n[CARGA DE CONJUNTO]\n");

    do {
        do {
            printf("Ingrese la cantidad de elementos a cargar: ");
            fflush(stdin);
            fgets(num, TAMANO_NUM, stdin);
            entrada = esEntero(num) && esEnter(num);
        } while (!entrada);
        cantidadElementos = convertirChar(num);
        entrada = numeroRango(cantidadElementos,0,100);
    } while (!entrada);
    while (i < cantidadElementos){
        do{
            printf("Ingrese el elemento numero #%d: ", i + 1);
            fflush(stdin);
            fgets(num, TAMANO_NUM, stdin);
            entrada = esEntero(num) && esEnter(num);
        } while (!entrada);
        i++;
        numero = convertirChar(num);
        elemento = te_crear(numero);
        cto_agregar (c, elemento);
    }
}

void cargarConjuntosNaturales(Conjunto c) {
    bool entrada = true;
    char num[TAMANO_NUM];
    int cantidadElementos, opcion, numero, i = 0;
    TipoElemento elemento;

    printf("\n[CARGA DE CONJUNTO]\n");

    do {
        do {
            printf("Ingrese la cantidad de elementos a cargar: ");
            fflush(stdin);
            fgets(num, TAMANO_NUM, stdin);
            entrada = esEntero(num) && esEnter(num);
        } while (!entrada);
        cantidadElementos = convertirChar(num);
        entrada = numeroRango(cantidadElementos,0,100);
    } while (!entrada);
    while (i < cantidadElementos){
        do{
            do{
                printf("Ingrese el elemento numero #%d: ", i + 1);
                fflush(stdin);
                fgets(num, TAMANO_NUM, stdin);
                entrada = esEntero(num) && esEnter(num);
            } while (!entrada);
            numero = convertirChar(num);
            entrada = numeroRango(numero, 1, 2000000000);
        } while (!entrada);
        i++;

        elemento = te_crear(numero);
        cto_agregar(c, elemento);
    }
}

// ================== EJERCICIOS ==================

// funcion que es capaz de resolver la diferencia simétrica entre dos conjuntos
Conjunto diferenciaSimetrica (Conjunto A, Conjunto B) {
    Conjunto cUnion = cto_union(A, B);
    Conjunto cInterseccion = cto_interseccion(A, B);

    return cto_diferencia(cUnion, cInterseccion);
}

int main() {
    printf("\n[EJERCICIO5]\n");

    Conjunto conjuntoA = cto_crear();
    Conjunto conjuntoB = cto_crear();

    printf("[CONJUNTO A - CARGA]\n");
    cargarConjunto(conjuntoA);
    printf("\n----------------\n");
    printf("[CONJUNTO B - CARGA]\n");
    cargarConjunto(conjuntoB);
    printf("\n----------------\n");

    printf("[CONJUNTO DIFERENCIA SIMETRICA]\n");
    cto_mostrar(diferenciaSimetrica(conjuntoA, conjuntoB));

    return 0;
}
