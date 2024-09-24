#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "pilas.h"

// Funcion que elimina los espacios de una cadena de char ingresada (VALIDACION)
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

// funcion para leer un entero por teclado (validacion)
int leer_entero() {
    char entrada[100];
    long numero;
    char *finptr;
    int valido = 0;

    while (!valido) {
        printf("Ingrese un numero entero: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        if (entrada[0] == '\0') {
            printf("Entrada invalida. Intentelo de nuevo.\n");
            continue;
        }
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 100000 || numero < -100000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion a la que se le ingresa una pila y se calcula su longitud
int longitudPila (Pila pila) {
    // la complejidad algoritmica de este algoritmo es O(n).
    int longitud = 0;
    Pila aux = p_crear();
    while (!p_es_vacia(pila)) {
        p_apilar(aux, p_desapilar(pila));
        longitud++;
    }
    while (!p_es_vacia(aux)) {
        p_apilar(pila, p_desapilar(aux));
    }
    return longitud;
}

// funcion a la que se le ingresa una pila y se rellena por teclado
Pila llenarPila(Pila pila) {
    // la complejidad algoritmica de este algoritmo es O(n^2).
    int longitud = 0;
    printf("Ingrese la longitud de la pila (tamano de 0 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    longitud = leer_entero();


    while (longitud <= 0 || longitud > 100000) {
        if (longitud == 0){
            break;
        }
        else if (longitud < 1 || longitud > 100000){
            printf("Entrada invalida. Se encuentra fuera del rango disponible para la pila. Reingrese el tamanio. ");
            longitud = leer_entero();
        }
    }
    int i = 1;
    while (i <= longitud){
        if (p_es_llena(pila)){
            printf("La pila ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
            int ingreso = 0;
            printf("Ingrese el elemento %d (entre -100.000 y 100.000).\n", i);
            ingreso = leer_entero();
            TipoElemento elemento = te_crear(ingreso);
            p_apilar(pila, elemento);
            i++;
    }
    return pila;
}

// funcion que indica si las pilas son distintas o iguales
bool p_ej3_iguales(Pila p1, Pila p2) {
    // la complejidad algoritmica de este algoritmo es O(n) siendo n la cantidad de elementos de la pila
    bool iguales = true;
    Pila pilaAux = p_crear();

    if (longitudPila(p1) != longitudPila(p2)) {
        iguales = false;
        printf("Pilas de longitud diferente!\n");
    } else {
        while (!p_es_vacia(p1)) {
            if (p_tope(p1)->clave != p_tope(p2)->clave) {
                iguales = false;
            }
            p_apilar(pilaAux, p_desapilar(p1));
            p_apilar(pilaAux, p_desapilar(p2));
        }
        while (!p_es_vacia(pilaAux)) {
            p_apilar(p1, p_desapilar(pilaAux));
            p_apilar(p2, p_desapilar(pilaAux));
        }
    }
    return iguales;
}

int main() {
    Pila pila1 = p_crear();
    Pila pila2 = p_crear();
    // ingresar pilas
    printf("[PILA 1]\n");
    pila1 = llenarPila(pila1);
    p_mostrar(pila1);
    printf("\n[PILA 2]\n");
    pila2 = llenarPila(pila2);
    p_mostrar(pila2);
    // comparar pilas
    if (p_ej3_iguales(pila1, pila2)) {
        printf("\nLas pilas son iguales!.\n");
    } else {
        printf("\nLas pilas son distintas!.\n");
    }
}
