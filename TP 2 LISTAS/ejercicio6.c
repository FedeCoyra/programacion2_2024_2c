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

// funcion para chequear lo que pasa si una de las listas (o ambas) es vacia
bool revisar_listas_vacias (Lista lista1, Lista lista2) {
    if (l_es_vacia(lista1) && l_es_vacia(lista2)) {
        printf("Ambas listas son sublista de la otra, ya que las dos son listas vacias (e iguales).\n");
        return true;
    } else if (l_es_vacia(lista1)) {
        printf("L1 es sublista de L2.\n");
        return true;
    } else if (l_es_vacia(lista2)) {
        printf("L2 es sublista de L1.\n");
        return true;
    } else {
        return false;
    }
}

// funcion que indica si una lista es sublista de la otra
bool es_sublista (Lista principal, Lista secundaria) { // O(m * n) -> mayor complejidad
    Iterador iterSecundaria = iterador(secundaria);
    while (hay_siguiente(iterSecundaria)) {
        TipoElemento elementoS = siguiente(iterSecundaria);
        bool encontrado = false;
        Iterador iterPrincipal = iterador(principal);
        while (hay_siguiente(iterPrincipal)) {
            TipoElemento elementoP = siguiente(iterPrincipal);
            if (elementoP->clave == elementoS->clave) {
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            return false;
        }
    }
    return true;
}

// funcion para ingresar valores a una lista desde el teclado
void inputLista(Lista lista) {
    printf("Ingrese los elementos (-10M a 10M) de la lista. Ingrese '*' para terminar:\n");
    int clave = 1;
    char input[100];
    int contador = 0;
    Lista claves_ingresadas = l_crear();
    do {
        printf("Clave #%d: ", (contador + 1));
        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = '\0';
        strtrim(input);
        if (strcmp(input, "*") == 0) {
            break;
        }
        int num;
        if (sscanf(input, "%d", &num) != 1) {
            printf("El valor ingresado no es un numero entero. Ingrese un valor valido.\n");
            continue;
        }
        if (l_buscar(claves_ingresadas, num) != NULL) {
            printf("La clave ya ha sido ingresada. Ingrese una clave distinta.\n");
            continue;
        }

        // convertir la entrada a un numero entero
        char *endptr;
        long numero = strtol(input, &endptr, 10);

        // verificar si se ingreso un numero valido
        if (*endptr != '\0' || numero > 10000000 || numero < -10000000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
            continue;
        }
        TipoElemento elemento = (TipoElemento) malloc(sizeof(struct TipoElementoRep));
        elemento->clave = num;
        l_agregar(lista, elemento);
        TipoElemento elemento_copia = te_crear(num);
        l_agregar(claves_ingresadas, elemento_copia);
        contador++;
        if (l_es_llena(lista)) {
            printf("La lista ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        clave++;
    } while (1);
}

int main() {
    Lista lista1 = l_crear();
    Lista lista2 = l_crear();
    printf("LISTA 1\n");
    inputLista(lista1);
    printf("LISTA 2\n");
    inputLista(lista2);
    if (revisar_listas_vacias(lista1, lista2)) {
        return 0;
    } else {
        printf("\n");
        printf("LISTA 1. ");
        l_mostrar(lista1);
        printf("\n");
        printf("LISTA 2. ");
        l_mostrar(lista2);
        printf("\n");
        printf("-----------------------\n");
        printf("SON SUBLISTA? \n");
        printf("\n");
        if (es_sublista(lista1, lista2)) {
            printf("L2 es sublista de L1");
        } else {
            printf("L2 no es sublista de L1");
        }

        printf("\n");

        if (es_sublista(lista2, lista1)) {
            printf("L1 es sublista de L2");
        } else {
            printf("L1 no es sublista de L2");
        }
        printf("\n");
    }
}
