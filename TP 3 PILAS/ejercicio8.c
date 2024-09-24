#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "pilas.h"

// Funcion para cargar pila y vaciarla | complejidad algoritmica O(N)
void vaciarYCargar(Pila P1, Pila P2) {
    while(!p_es_vacia(P1)) {
        p_desapilar(P1);
    }
    while(!p_es_vacia(P2)) {
        TipoElemento X1 = p_desapilar(P2);
        p_apilar(P1, X1);
    }
}

// funcion para retornar una pila con la cantidad de apariciones de cada elemento | complejidad algoritmica O(N^2)
Pila p_ej8_sacarrepetidos(Pila p) {
    Pila PR = p_crear();
    Pila PAux1 = p_crear();
    int *contPuntero = (int*) malloc(sizeof(int)* 10);
    int contEntero = 0;
    while(!p_es_vacia(p)) {
        TipoElemento X1 = p_desapilar(p);
        contEntero = 1;
        while(!p_es_vacia(p)) {
            TipoElemento X2 = p_desapilar(p);
            if(X1->clave != X2->clave) {
                p_apilar(PAux1, X2);
            } else {
                contEntero++;
            }
        }
        vaciarYCargar(p, PAux1);
        X1->valor = malloc(sizeof(int)); // Asignar memoria para el contador de repeticiones
        *(int*)(X1->valor) = contEntero;
        p_apilar(PR,X1);
    }
    return PR;
}

// funcion que copia una pila sin perder la original | complejidad algoritmica O(N)
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

// funcion que muestra los datos | complejidad O(N)
void p_mostrar_claves(Pila P) {
    TipoElemento elemento;
    Pila Paux = p_crear();
    Paux = copiar_pila(P);
    printf("\n[REPETICIONES]\n");
    if (p_es_vacia(P)) {
        printf("No hay elementos repetidos.\n");
    }
    while(!p_es_vacia(P)) {
        elemento = p_desapilar(P);
        printf("%d:%d", elemento->clave, *(int*)elemento->valor);
        p_apilar(Paux,elemento);
        if(!p_es_vacia(P)){
            printf(", ");
        }
    }
    while(!p_es_vacia(Paux)) {
        p_apilar(P,p_desapilar(Paux));
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

int main(){
    printf("[INGRESO PILA]\n");
    Pila P1 = rellenar_pila_por_teclado();
    p_mostrar(P1);

    Pila P2 = copiar_pila(P1);
    P2 = p_ej8_sacarrepetidos(P2);
    p_mostrar_claves(P2);
}
