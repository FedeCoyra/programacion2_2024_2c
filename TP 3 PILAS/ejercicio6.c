#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include "pilas.h"

// funcion que copia una pila sin alterar la original
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

// Funcion que elimina de una pila un elemento segun su clave de manera ITERATIVA -> O(n)
 Pila eliminarclaveIterativa(Pila p, int clave) {
     if (p_es_vacia(p)) {
         return p;
     }

     Pila Paux = p_crear();
     TipoElemento elemento;

     while(!p_es_vacia(p)) { // n
         elemento = p_desapilar(p);
         if (clave != elemento->clave){
             p_apilar(Paux, elemento);
         }
     }

     while (!p_es_vacia(Paux)) { // n
         p_apilar(p, p_desapilar(Paux));
     }

     return p;
}

// Funcion que elimina un elemento de la pila RECURSIVAMENTE -> O(n)
Pila eliminarclaveRecursiva(Pila p, int clave) {
    if (p_es_vacia(p)) {
        return p;
    }

    TipoElemento elemento = p_desapilar(p);
    eliminarclaveRecursiva(p, clave);

    if (clave != elemento->clave) {
        p_apilar(p, elemento);
    }

    return p;
}

// funcion que carga de manera aleatoria una pila ingresada por parametro
void cargar_random(Pila P) {
    srand(time(NULL));
    for (int i = 0; i < 100000; i++) {  //Solo se cargara el  tamanio maximo permitido por la TAD.
        p_apilar(P, te_crear(rand()%10));
    }
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

// funcion para cargar una pila manualmente
Pila rellenar_pila_por_teclado() {
    Pila pila = p_crear();
    int longitudPila = 0;
    printf("Ingrese la longitud de la pila (tamanio de 1 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    longitudPila = leer_entero();
    while (longitudPila < 1 || longitudPila > 100000) {
        printf("Entrada invalida. Se encuentra fuera del rango disponible para la pila. Reingrese el tamanio: ");
        longitudPila = leer_entero();
    }

    int i = 1;
    while (i <= longitudPila) {
        if (p_es_llena(pila)) {
            printf("La pila ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        int ingreso = 0;
        printf("Ingrese el elemento %d (entre -100.000 y 100.000):\n", i);
        ingreso = leer_entero();
        TipoElemento elemento = te_crear(ingreso);
        p_apilar(pila, elemento);
        i++;
    }
    return pila;
}

void main() {
    int opcion;
    Pila P = p_crear();

    do {
        do {
            printf("Seleccione una opcion:\n");
            printf("1. Cargar pila de forma aleatoria\n");
            printf("2. Cargar pila manualmente\n");
            printf("0. Salir\n");
            opcion = leer_entero();

            if (opcion < 0 || opcion > 2) {
                printf("Opcion invalida. Intente nuevamente.\n");
            }
        } while (opcion < 0 || opcion > 2);
        switch(opcion) {
            case 1:
                cargar_random(P);
                printf("[PILA CARGADA ALEATORIAMENTE]\n");
                p_mostrar(P);
                break;
            case 2:
                P = rellenar_pila_por_teclado();
                printf("[PILA CARGADA MANUALMENTE]\n");
                p_mostrar(P);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
        }

        if (opcion != 0) {
            // copio la pila original para no perderla y procedo a eliminar la clave pedida
            printf("[ELIMINAR]\n");
            printf("Valores entre (-100.000 y 100.000)\n");
            Pila nuevaPila = copiar_pila(P);
            int n = leer_entero();
            printf("Eliminando elemento/s con clave %d de manera RECURSIVA.\n", n);
            p_mostrar(eliminarclaveRecursiva(nuevaPila, n));
            printf("\n");
            printf("[PILA ORIGINAL]\n");
            p_mostrar(P);
            printf("\n");
            printf("Eliminando elemento/s con clave %d de manera ITERATIVA.\n", n);
            p_mostrar(eliminarclaveIterativa(nuevaPila, n));
            printf("\n");

            // muestro la pila original nuevamente para demostrar que no se perdio
            printf("[PILA ORIGINAL]\n");
            p_mostrar(P);
            printf("\n");
        }

    } while (opcion != 0);
}
