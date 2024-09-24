#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "pilas.h"

// funcion que pide una pila y retorna su copia sin corromper ni cambiar la original
Pila copiar_pila(Pila pilaOriginal) {
    Pila pilaAuxiliar = p_crear();
    Pila pilaCopia = p_crear();
    while (!p_es_vacia(pilaOriginal)) {
        TipoElemento elemento = p_desapilar(pilaOriginal);
        p_apilar(pilaAuxiliar, elemento);
    }
    while (!p_es_vacia(pilaAuxiliar)) {
        TipoElemento elemento = p_desapilar(pilaAuxiliar);
        p_apilar(pilaOriginal, elemento);
        p_apilar(pilaCopia, elemento);
    }
    return pilaCopia;
}

// funcion que invierte una pila ingresada y la retorna
Pila p_ej5_invertir(Pila p) {
    Pila inversa = p_crear();
    TipoElemento elemento;
    // invierte los elementos desapilando la pila
    while (!p_es_vacia(p)) {
        elemento = p_desapilar(p);
        p_apilar(inversa, elemento);
    }
    return inversa;
}

// funcion que elimina los espacios de una cadena de char ingresada
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

// funcion que crea una pila, la carga por teclado y la retorna
Pila rellenar_pila_por_teclado() { // O(n)
    Pila pila = p_crear();
    int longitudPila = 0;
    printf("Ingrese la longitud de la pila (tamano de 1 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    longitudPila = leer_entero();
    while (longitudPila < 1 || longitudPila > 100000) {
            printf("Entrada invalida. Se encuentra fuera del rango disponible para la pila. Reingrese el tamanio. ");
            longitudPila = leer_entero();
    }

    int i = 1;
    while (i <= longitudPila){
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

void main() {
    printf("[INGRESO PILA] \n");
    Pila pilaIngresada = rellenar_pila_por_teclado();
    printf("\n[PILA ORIGINAL]\n");
    p_mostrar(pilaIngresada);
    Pila pilaCopiada = copiar_pila(pilaIngresada);
    printf("\n[PILA INVERTIDA]\n");
    p_mostrar(p_ej5_invertir(pilaCopiada));
    printf("\n[PILA ORIGINAL]\n");
    p_mostrar(pilaIngresada);
}
