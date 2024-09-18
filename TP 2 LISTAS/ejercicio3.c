#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "listas.h"


// Funcion que elimina los espacios de un string ingresado por teclado (VALIDACION)
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

// Funcion para leer un entero por teclado (VALIDACION)
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
            printf("Entrada invalida (rango de -100k a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

int leer_entero_sin_cero() {
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
        if (errno != 0 || *finptr != '\0' || numero > 100000 || numero < -100000 || numero == 0) {
            printf("Entrada invalida (rango de -100k a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// Funcion que pide una lista y su tamaño, y al rellena con numeros del teclado
Lista rellenarListaSinCero(Lista listaNueva, int tamanio) {
    int i = 1;
    int valorLista = 0;
    while (i <= tamanio) {
        if (l_es_llena(listaNueva)) {
            printf("La lista ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        printf("Ingrese un valor a la lista #%d: ", i);
        valorLista = leer_entero_sin_cero();
        TipoElemento elemento = te_crear(valorLista);
        l_agregar(listaNueva, elemento);
        i++;
    }
    return listaNueva;
}

// funcion que pide dos listas y dice si una es multiplo de la otra
bool multiploLista (Lista l1, Lista l2) {
    bool res = true;
    bool es_escalar = true;
    int n1, n2, escala, escala_ant = 0;
    // si son iguales
    if (l_longitud(l1) == l_longitud(l2)) {
        n1 = l_recuperar(l1, 1)->clave;
        n2 = l_recuperar(l2, 1)->clave;
        escala = n2/n1;
        escala_ant = escala;
        // compara los elementos de cada lista
        Iterador iter1 = iterador(l1);
        Iterador iter2 = iterador(l2);
        TipoElemento elemento1;
        TipoElemento elemento2;
        while (hay_siguiente(iter1)) {
            elemento1 = siguiente(iter1);
            elemento2 = siguiente(iter2);
            escala = elemento2->clave / elemento1->clave;
            if (elemento2->clave % elemento1->clave != 0 ) {
                res = false;
            }
            if (escala != escala_ant) {
                es_escalar = false;
            }
            escala_ant = escala;
        }

    } else {
        // de ser distintas retorna false
        printf("Listas con longitud diferente (por ende L2 no es multiplo de L1)!\n");
        res=false;
    }
    if (res == true) {
        printf("L2 es multiplo de L1\n");
        if (es_escalar) {
            printf("Es un escalar.\n");
        }
    } else if (res == false) {
        printf("L2 no es multiplo de L1\n");
    }
    return res;
}

// Funcion que pide una lista y su tamaño, y al rellena con numeros del teclado
Lista rellenarLista(Lista listaNueva, int tamanio) {
    int i = 1;
    int valorLista = 0;
    while (i <= tamanio) {
        if (l_es_llena(listaNueva)) {
            printf("La lista ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        printf("Ingrese un valor a la lista #%d: ", i);
        valorLista = leer_entero();
        TipoElemento elemento = te_crear(valorLista);
        l_agregar(listaNueva, elemento);
        i++;
    }
    return listaNueva;
}

void main() {
    // OBTENGO TAMAÑO LISTA 2
    printf("Ingrese el tamanio de la LISTA 2 (1 a 100): ");
    int tamanio = 0;
    tamanio = leer_entero();
    while (tamanio <= 0) {
        printf("Fuera de rango, ingrese nuevamente el tamanio: ");
        tamanio = leer_entero();
    }
    Lista lista2 = l_crear();
    lista2 = rellenarLista(lista2, tamanio);
    l_mostrar(lista2);

    // OBTENGO TAMAÑO LISTA 1
    Lista lista1 = l_crear();
    printf("Ingrese el tamanio de la LISTA 1 (1 a 100): ");
    tamanio = 0;
    tamanio = leer_entero_sin_cero();
    while (tamanio <= 0) {
        printf("Fuera de rango, ingrese nuevamente el tamanio: ");
        tamanio = leer_entero_sin_cero();
    }
    lista1 = rellenarListaSinCero(lista1, tamanio);
    l_mostrar(lista1);
    // MULTIPLO
    multiploLista(lista1, lista2);
}
