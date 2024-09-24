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
            printf("Entrada invalida (rango entero de -100k a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion que pide una pila y retorna su longitud
int longitudPila (Pila pila) {
    // la complejidad algoritmica de este algoritmo es O(n)
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

// funcion que convierte un numero entero a la base indicada
char* p_ej4_cambiarbase(int nrobasedecimal, int nrootrabase) {
    char *nuevoNum = malloc(sizeof(char) * ( 100 + 1 ));
    char *ptr = nuevoNum;
    if (nrobasedecimal < 0) {
        *ptr = '-';
        ptr++;
    }

    // la complejidad algoritmica es O(n) siendo n la cantidad de digitos del numero
    Pila pila = p_crear();
    if (nrobasedecimal < 0) {
        nrobasedecimal = nrobasedecimal * -1;
    }
    int numeroAConvertir = nrobasedecimal;
    if (numeroAConvertir == 0) {
        TipoElemento elemento = te_crear(0);
        p_apilar(pila, elemento);
        strcpy(nuevoNum, "0");
        return nuevoNum;
    }

    int contadorParaMax = 0;
    while (numeroAConvertir > 0) {
        int resto = numeroAConvertir % nrootrabase;
        TipoElemento elemento = te_crear(resto);
        p_apilar(pila, elemento);
        numeroAConvertir = numeroAConvertir / nrootrabase;
        contadorParaMax++;
    }

    while (!p_es_vacia(pila)) {
        TipoElemento elemento = p_desapilar(pila);
        if (elemento->clave < 10) {
            *ptr = elemento->clave + '0';
            ptr++;
        } else {
            *ptr = elemento->clave + 55;
            ptr++;
        }
    }
    *ptr = '\0';

    return nuevoNum;
}

int main() {
    int numero = 0;
    printf("Ingrese el numero a convertir: ");
    numero = leer_entero();

    int base = 0;
    printf("Ingrese la base a la que desea convertir la base (2 - 16): ");
    base = leer_entero();
    while (base < 2 || base > 16) {
        printf("El valor ingresado es invalido. Ingrese un numero entero entre 2 y 16: ");
        base = leer_entero();
    }

    char * nuevoNum = p_ej4_cambiarbase(numero, base);
    printf ("\nTenga en cuenta que si la conversion a otra base posee muchos digitos\n");
    printf ("se mostrara hasta llenar el tamanio maximo de la pila!\n\n");
    printf("El numero %d en base %d es: %s", numero, base, nuevoNum);
}
