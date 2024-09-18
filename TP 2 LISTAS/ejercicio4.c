#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include "listas.h"

// funcion que elimina espacios en blanco de una cadena
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

// funcion que compara dos listas y se fija si una es mayor, menor o igual a la otra
int comparar(Lista L1, Lista L2) { // O(n) -> mayor complejidad
    int MAYOR = 0;
    int MENOR = 1;
    int IGUAL = 2;
    TipoElemento elemento1;
    TipoElemento elemento2;

    Iterador iter1 = iterador(L1);
    Iterador iter2 = iterador(L2);

    int contL1 = 0;
    int contL2 = 0;

    while (hay_siguiente(iter1)) {
        elemento1 = te_crear(siguiente(iter1)->clave);
        elemento2 = te_crear(siguiente(iter2)->clave);
        if (((elemento1->clave)) > ((elemento2->clave))) {
            contL1++;
        } else if(((elemento2->clave)) > ((elemento1->clave))) {
            contL2++;
        };
    }

    if (contL1 > contL2) {
        return MAYOR;
    } else if(contL2 > contL1) {
        return MENOR;
    } else return IGUAL;
}

// funcion que pide una lista y su tamaño, y al rellena con numeros del teclado
Lista rellenarLista(Lista listaNueva, int tamanio) {
    int i = 1;
    int valorLista = 0;
    while (i <= tamanio) {
        if (l_es_llena(listaNueva)) {
            printf("La lista ha alcanzado su capacidad maxima y no puede recibir ni mostrar mas elementos.\n");
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


int main() {
    // OBTENGO EL TAMAÑO DE LAS LISTAS
    printf("Ingrese el tamanio de las listas (0 a 100): ");
    int tamanio ;
    tamanio = leer_entero();
    if (tamanio == 0){
        printf("Las listas estan vacias, son IGUALES.\n");
        return 0;
    }
    while (tamanio < 0) {
        printf("Fuera de rango, ingrese nuevamente el tamanio: ");
        tamanio = leer_entero();
    }

    // CREO LAS LISTAS Y PIDO LOS DATOS
    Lista lista1 = l_crear();
    printf("--- Ingrese los datos para la LISTA 1 ---\n");
    lista1 = rellenarLista(lista1, tamanio);

    Lista lista2 = l_crear();
    printf("--- Ingrese los datos para la LISTA 2 ---\n");
    lista2 = rellenarLista(lista2, tamanio);

    l_mostrar(lista1);
    l_mostrar(lista2);

    if (comparar(lista1, lista2) == 0) {
        printf("La lista 1 es MAYOR a la lista 2");
    } else if(comparar(lista1, lista2) == 1) {
        printf("La lista 1 es MENOR a la lista 2");
    } else printf("La lista 1 es IGUAL a la lista 2");
}
