#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "colas.h"

// funcion que busca un elemento en la cola y retorna si esta o no
bool estaEnCola(Cola cola, int clave) {
    TipoElemento X;
    bool existe = false;
    Cola cAux = c_crear();
    while (!c_es_vacia(cola)) {
        X = c_desencolar(cola);
        c_encolar(cAux, X);
        if (X->clave == clave) {
            existe = true;
        }
    }
    while (!c_es_vacia(cAux)) {
        c_encolar(cola, c_desencolar(cAux));
    }
    return existe;
}

// funcion que copia una cola ingreasada por parametro y retorna su copia (sin perder la original)
Cola copiarCola(Cola cola) {
    Cola cAux = c_crear();
    Cola cCopia = c_crear();
    TipoElemento X;
    while (!c_es_vacia(cola)) {
        X = c_desencolar(cola);
        c_encolar(cAux, X);
        c_encolar(cCopia, X);
    }
    while (!c_es_vacia(cAux)) {
        c_encolar(cola, c_desencolar(cAux));
    }
    return cCopia;
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

// funcion que rellena una cola por teclado, sin tomar repetidos ni menor a 2
Cola rellenar_colas_por_teclado_sin_repetidos() {
    Cola cola = c_crear();
    int longitudCola = 0;
    printf("Ingrese la longitud de la cola (entre 1 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la cola, solo se cargaran hasta que se llene la misma.\n");
    longitudCola = leer_entero();
    while (longitudCola < 1 || longitudCola > 100000) {
        printf("Entrada invalida. Fuera del rango disponible para la cola. Reingrese el tamanio. ");
        longitudCola = leer_entero();
    }
    int i = 1;

    for (int i = 0; i < longitudCola; i++) {
        int ingreso = 0;
        if (c_es_llena(cola)) {
            printf("La cola ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        printf("Ingrese el elemento %d. ", i + 1);
        printf("El rango debe estar entre 2 y 100.000.\n");
        ingreso = leer_entero();
        while (estaEnCola(cola, ingreso) || (ingreso < 2)) {
            printf("El elemento ya existe o es menor 2, ingrese otro :");
            printf("\nIngrese el elemento %d. ", i + 1);
            ingreso = leer_entero();
        }
        TipoElemento elemento = te_crear(ingreso);
        c_encolar(cola, elemento);
    }
    return cola;
}

// funcion que cuenta los elementos de una cola
float longitud_cola(Cola c) {
    Cola cAux = c_crear();
    float contador = 0;
    while (!c_es_vacia(c)) {
        c_encolar(cAux, c_desencolar(c));
        contador++;
    }
    while (!c_es_vacia(cAux)) {
        c_encolar(c, c_desencolar(cAux));
    }
    return contador;
}

// funcion que retorna el divisor entero (total o parcial) de una cola
int c_ej5_divisortotal(Cola c, bool *fuetotal) {
    if (c_es_vacia(c)) {
        return 0;
    }
    Cola copia1 = copiarCola(c);
    Cola copia2 = copiarCola(c);
    Cola cAux = c_crear();
    TipoElemento elemento1;
    TipoElemento elemento2;
    int contador = 0;
    int divisor = 0;
    float longitudCola = longitud_cola(c);
    *fuetotal = false;

    while (!c_es_vacia(copia1)) {
        elemento1 = c_desencolar(copia1);
        while (!c_es_vacia(copia2)) {
            elemento2 = c_desencolar(copia2);
            if ((elemento2->clave % elemento1->clave) == 0) {
                contador++;
            }
            c_encolar(cAux, elemento2);
        }
        if (contador == longitudCola) {
            *fuetotal = true;
            return elemento1->clave;
        } else {
            float mitadLongitud = longitudCola / 2;
            if (contador >= mitadLongitud && divisor == 0) {
                divisor = elemento1->clave;
            }
        }
        while (!c_es_vacia(cAux)) {
            c_encolar(copia2, c_desencolar(cAux));
        }
        contador = 0;
    }
    return divisor;
}

int main() {
    // ingreso de datos
    printf("[INGRESO DATOS]\n");
    Cola c = c_crear();
    c = rellenar_colas_por_teclado_sin_repetidos(c);
    c_mostrar(c);
    printf("\n=======================\n");
    // ejercicio
    bool fuetotal;
    int divisor = c_ej5_divisortotal(c, &fuetotal);
    if (divisor != 0) {
        if (fuetotal) {
            printf("Se encontro un divisor TOTAL: %d.\n", divisor);
        } else {
            printf("Se encontro un divisor PARCIAL: %d.\n", divisor);
        }
    } else {
        printf("No se encontro divisor total o parcial.\n");
    }

    return 0;
}
