#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "pilas.h"

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

// funcion que copia una pila sin alterar su version original
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

// funcion que rellena una pila por teclado
Pila rellenar_pila_por_teclado() {
    Pila pila = p_crear();
    int longitudPila = 0;
    printf("Ingrese la longitud de la pila (tamano de 0 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    longitudPila = leer_entero();
    while (longitudPila <= 0 || longitudPila > 100000) {
        if (longitudPila == 0){
            break;
        }
        else if (longitudPila < 1 || longitudPila > 100000){
            printf("Entrada invalida. Se encuentra fuera del rango disponible para la pila. Reingrese el tamanio. ");
            longitudPila = leer_entero();
        }
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

// funcion que pide una pila y devuelve su longitud
int longitud_pila(Pila pila) {
    Pila pilaAux = copiar_pila(pila);
    int contador = 0;
    while (!p_es_vacia(pilaAux)) {
        p_desapilar(pilaAux);
        contador++;
    }
    return contador;
}

// funcion que pide una pila y elimina sus claves repetidas
void eliminar_repetidos(Pila pila) {
    Pila pilaAux = p_crear();
    while (!p_es_vacia(pila)) {
        TipoElemento elemento = p_desapilar(pila);
        bool encontrado = false;
        Pila pilaCopia = copiar_pila(pilaAux);
        while (!encontrado && !p_es_vacia(pilaCopia)) {
            TipoElemento elementoCopia = p_desapilar(pilaCopia);
            if (elemento->clave == elementoCopia->clave) {
                encontrado = true;
            }
        }
        if (!encontrado) {
            p_apilar(pilaAux, elemento);
        }
    }
    while (!p_es_vacia(pilaAux)) {
        TipoElemento elemento = p_desapilar(pilaAux);
        p_apilar(pila, elemento);
    }
}

// funcion que recorre dos pilas y retorna aquellos elementos repetidos
Pila p_ej7_elementoscomunes(Pila p1, Pila p2) {
    Pila pilaCopiaA = copiar_pila(p1);
    Pila pilaCopiaB = copiar_pila(p2);
    Pila pilaRepetidos = p_crear();

    while (!p_es_vacia(pilaCopiaA)) {
        TipoElemento elementoA = p_desapilar(pilaCopiaA);
        bool encontrado = false;
        while (!encontrado && !p_es_vacia(pilaCopiaB)) {
            if (elementoA->clave == p_desapilar(pilaCopiaB)->clave) {
                p_apilar(pilaRepetidos, elementoA);
                encontrado = true;
            }
        }
        pilaCopiaB = copiar_pila(p2);
    }
    eliminar_repetidos(pilaRepetidos);
    return pilaRepetidos;
}

int main() {
    printf("[PILA A]\n");
    Pila pilaA = rellenar_pila_por_teclado();
    printf("\n[PILA B]\n");
    Pila pilaB = rellenar_pila_por_teclado();
    printf("\n----------------------\n");
    printf("\n[PILA A] \n");
    p_mostrar(pilaA);
    printf("\n[PILA B] \n");
    p_mostrar(pilaB);
    printf("\n----------------------\n");
    Pila repetidos = p_crear();
    repetidos = p_ej7_elementoscomunes(pilaA, pilaB);
    printf("\n[REPETIDOS] \n");
    if (p_es_vacia(repetidos)) {
        printf("No hay elementos repetidos.\n");
    } else {
        p_mostrar(repetidos);
    }
    printf("\n");
    return 0;
}
