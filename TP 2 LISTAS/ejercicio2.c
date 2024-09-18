#include "listas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// Dada una 2 listas (L1 y L2) cargadas con valores al azar (en la clave) realizar los siguientes.

// a. Que retorne una lista con los valores de L1 que no están en L2.
Lista valoresFaltantesL1(Lista lista1, Lista lista2) {
    Lista listaResultante = l_crear();
    Iterador iterL1 = iterador(lista1);
    bool estaEnLista;
    while (hay_siguiente(iterL1)) {
        TipoElemento elementoL1 = siguiente(iterL1);
        Iterador iterL2 = iterador(lista2);
        estaEnLista = false;
        if (elementoL1) {
            while (hay_siguiente(iterL2)) {
                TipoElemento elementoL2 = siguiente(iterL2);
                if (elementoL1->clave == elementoL2->clave) {
                    estaEnLista = true;
                }
            }
            if (!estaEnLista) {
                l_agregar(listaResultante, elementoL1);
            }
        }
    }
    return listaResultante;
}

// b. Que retorne una lista con los valores de L2 que no están en L1.
Lista valoresFaltantesL2(Lista lista1, Lista lista2) {
    Lista listaResultante = l_crear();
    Iterador iterL2 = iterador(lista2);
    bool estaEnLista;
    while (hay_siguiente(iterL2)) {
        TipoElemento elementoL2 = siguiente(iterL2);
        Iterador iterL1 = iterador(lista1);
        estaEnLista = false;
        if (elementoL2) {
            while (hay_siguiente(iterL1)) {
                TipoElemento elementoL1 = siguiente(iterL1);
                if (elementoL2->clave == elementoL1->clave) {
                    estaEnLista = true;
                }
            }
            if (!estaEnLista) {
                l_agregar(listaResultante, elementoL2);
            }
        }
    }
    return listaResultante;
}

// c. Que retorne una lista con todos los valores comunes a ambas listas (L1 y L2).
Lista valoresComunes(Lista lista1, Lista lista2) {
    Lista listaResultante = l_crear();
    Iterador iterL1 = iterador(lista1);
    bool estaEnLista;
    while (hay_siguiente(iterL1)) {
        TipoElemento elementoL1 = siguiente(iterL1);
        estaEnLista = false;
        Iterador iterL2 = iterador(lista2);
        if (elementoL1) {
            while (hay_siguiente(iterL2)) {
                TipoElemento elementoL2 = siguiente(iterL2);
                if (elementoL1->clave == elementoL2->clave) {
                    estaEnLista = true;
                }
            }
            if (estaEnLista) {
                l_agregar(listaResultante, elementoL1);
            }
        }
    }
    return listaResultante;
}

// d. Que retorne los promedios de ambas listas.
char * promediosListas(Lista lista1, Lista lista2) {
    char *promedios = malloc(sizeof(char) * ( 100 + 1 ));

    // promedio lista1
    Iterador iterL1 = iterador(lista1);
    float promedioL1 = 0;
    while (hay_siguiente(iterL1)) {
        TipoElemento elementoL1 = siguiente(iterL1);
        promedioL1 += elementoL1->clave;
    }
    promedioL1 = promedioL1 / l_longitud(lista1);

    // promedio lista2
    Iterador iterL2 = iterador(lista2);
    float promedioL2 = 0;
    while (hay_siguiente(iterL2)) {
        TipoElemento elementoL2 = siguiente(iterL2);
        promedioL2 += elementoL2->clave;
    }
    promedioL2 = promedioL2 / l_longitud(lista2);

    sprintf(promedios, "L1: %.4f, L2: %.4f", promedioL1, promedioL2);
    return promedios;
}

// e. Que retorne el valor máximo de ambas listas y su posición ordinal.
char * maximoPosicionListas(Lista lista1, Lista lista2) {
    char * maxYPos = malloc(sizeof(char) * (100 + 1));
    // lista 1
    int maximoL1 = l_recuperar(lista1, 1)->clave;
    int posOrdinalL1 = 1;
    if (!l_es_vacia(lista1)) {
        int i = 1;
        Iterador iterL1 = iterador(lista1);
        while (hay_siguiente(iterL1)) {
            TipoElemento elementoL1 = siguiente(iterL1);
            if (elementoL1->clave > maximoL1) {
                maximoL1 = elementoL1->clave;
                posOrdinalL1 = i;
            }
            ++i;
        }
    }

    // lista 2
    int maximoL2 = l_recuperar(lista2, 1)->clave;
    int posOrdinalL2 = 1;
    if (!l_es_vacia(lista2)) {
        int i = 1;
        Iterador iterL2 = iterador(lista2);
        while (hay_siguiente(iterL2)) {
            TipoElemento elementoL2 = siguiente(iterL2);
            if (elementoL2->clave > maximoL2) {
                maximoL2 = elementoL2->clave;
                posOrdinalL2 = i;
            }
            ++i;
        }
    }

    sprintf(maxYPos, "[L1 Max: %d, pos %d], [L2 Max: %d, pos %d]", maximoL1, posOrdinalL1, maximoL2, posOrdinalL2);
    return maxYPos;
}

// funcion que elimina los espacios de un string ingresado por tecl
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

// funcion para leer un entero por teclado
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

// Funcion que recibe tamaño, y lista, y su rangos del random y retorna
Lista rellenarListaRandom() {
    Lista lista = l_crear();
    printf("[INGRESO - LISTA]\n");
    printf("Tamano de la lista.\n");
    printf("Al cargarse con valores al azar, solo se cargara el Tamanio maximo de la lista.\n");
    printf("En caso de excederse en el tamanio de la lista, se cargara el total permitido.\n");
    int tamano = leer_entero();
    while (tamano <= 0) {
        printf("Tamano invalido. Intentelo de nuevo. ");
        tamano = leer_entero();
    }
    // ---
    int randomMin = 0;
    int randomMax = 0;
    printf("[INGRESO - RANGO DE VALORES DEL RANDOM PARA CARGAR LISTA]\n");
    printf("Ingrese el valor minimo de los valores random: ");
    randomMin = leer_entero();
    printf("Ingrese el valor maximo de los valores random: ");
    randomMax = leer_entero();
    while (randomMax < randomMin) {
        printf("El valor maximo del rango no puede ser menor al minimo. Ingrese de vuelta: ");
        randomMax = leer_entero();
    }
    // ---
    int clave = 0;
    for (int i = 0; i < tamano; i++) {
        clave = randomMin + rand() % (randomMax - randomMin + 1);
        TipoElemento elemento = te_crear(clave);
        l_agregar(lista, elemento);
    }
    return lista;
}

void main() {
    // OBTENGO TAMAÑO LISTA 1
    printf("========== LISTA1 ==========\n");
    Lista lista1 = rellenarListaRandom();
    printf("========== LISTA2 ==========\n");
    Lista lista2 = rellenarListaRandom();
    printf("\n=============================\n");
    printf("LISTA1 - ");
    l_mostrar(lista1);
    printf("LISTA2 - ");
    l_mostrar(lista2);

    // a. Que retorne una lista con los valores de L1 que no están en L2.
    printf("\na. VALORES DE L1 QUE NO ESTAN EN L2\n");
    Lista listaA = valoresFaltantesL1(lista1, lista2);
    if (l_es_vacia(listaA)) {
        printf("No hay valores que cumplan (lista vacia).\n");
    } else {
       l_mostrar(listaA);
    }

    // b. Que retorne una lista con los valores de L2 que no están en L1.
    printf("\nb. VALORES DE L2 QUE NO ESTAN EN L1\n");
    Lista listaB = valoresFaltantesL2(lista1, lista2);
    if (l_es_vacia(listaB)) {
        printf("No hay valores que cumplan (lista vacia).\n");
    } else {
       l_mostrar(listaB);
    }

    // c. Que retorne una lista con todos los valores comunes a ambas listas (L1 y L2).
    printf("\nc. VALORES COMUNES EN AMBAS LISTAS\n");
    Lista listaC = valoresComunes(lista1, lista2);
    if (l_es_vacia(listaC)) {
        printf("No hay valores que cumplan (lista vacia).\n");
    } else {
        l_mostrar(listaC);
    }

    // d. Que retorne los promedios de ambas listas.
    printf("\nd. PROMEDIOS DE AMBAS LISTAS\n");
    char *promedios = malloc(sizeof(char) * ( 100 + 1 ));
    promedios = promediosListas(lista1, lista2);
    printf("%s", promedios);
    printf("\n");

    // e. Que retorne el valor máximo de ambas listas y su posición ordinal.
    printf("\ne. POSICION MAXIMA DE CADA LISTA CON POSICION ORDINAL\n");
    char * maxYPos = malloc(sizeof(char) * (100 + 1));
    maxYPos = maximoPosicionListas(lista1, lista2);
    printf("%s", maxYPos);
}
