#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "TP1_Recursividad.h"

const int TAM_MAX = 80;

// FUNCION TRIM PARA VALIDAR ENTRADA
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
    memmove(cadena, comienzoDeCadena, finalDeCadena - comienzoDeCadena + 2);
}

// FUNCION PARA VALIDAR QUE LA ENTRADA SEA ENTERA
int leer_entero_positivo_sin_cero() {
    char entrada[100];
    long numero;
    char *finptr;
    int valido = 0;
    while (!valido) {
        printf("Ingrese un numero entero: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero <= 0) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// RECURSIVAMENTE SE RESUELVE LA EXPLOSION
int * numeroExplosivoRecursivo(int numero, int bomba, int *resultado, int indice) {
    if (bomba == 1) {
        if (numero > 0) {
            resultado[indice] = 1;
            return numeroExplosivoRecursivo(numero - 1, bomba, resultado, ++indice);
        }
    } else if (numero <= bomba) {
        resultado[indice] = numero;
        indice += 1;
    } else if (numero == bomba) {
        resultado[indice] = numero;
    } else {
        numeroExplosivoRecursivo((numero/bomba), bomba, resultado, indice);
        numeroExplosivoRecursivo(numero-(numero/bomba), bomba, resultado, ++indice);
    }
    return resultado;
}

// FUNCION EXPLOSIVA
int* explosion (int n, int b) {
    int *arrayInt = calloc(TAM_MAX, sizeof(int));
    numeroExplosivoRecursivo(n, b, arrayInt, 0);

    return arrayInt;
}

// FUNCION QUE MUESTRA ARRAY DE ENTEROS
void mostrarArrayInt(int *array, int longitud) {
    printf("FRAGMENTOS: ");
    for (int i = 0; i < longitud; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// FUNCION QUE CUENTA ELEMENTOS DE UN ARRAY DE ENTEROS
int contarElementos(int *array) {
    int longitud = 0;
    while ((array[longitud] > 0) && (array[longitud] <= TAM_MAX)) {
        longitud++;
    }
    return longitud;
}

int main() {
    printf("Ingreso del numero explosivo positivo (min: 1 - max: %d). ", TAM_MAX);
    int numeroExplosivo = leer_entero_positivo_sin_cero();
    while (numeroExplosivo > TAM_MAX) {
        printf("Numero explosivo fuera de rango (min: 1 - max: %d). ", TAM_MAX);
        numeroExplosivo = leer_entero_positivo_sin_cero();
    }
    printf("Ingreso del numero bomba. ");
    int numeroBomba = leer_entero_positivo_sin_cero();
    // valido que no numero bomba sea mayor o igual que numero explosivo
    while (numeroBomba >= numeroExplosivo) {
        printf("\n");
        printf("--------------------");
        printf("\n");
        printf("El numero bomba no puede ser mayor o igual al numero explosivo.\n");
        printf("Ingreso del numero explosivo positivo (min: 1 - max: %d). ", TAM_MAX);
        numeroExplosivo = leer_entero_positivo_sin_cero();
        printf("Ingreso del numero bomba. ");
        numeroBomba = leer_entero_positivo_sin_cero();
    }

    int *arrayInt = calloc(TAM_MAX, sizeof(int));
    arrayInt = explosion(numeroExplosivo, numeroBomba);

    int longitud = contarElementos(arrayInt);
    mostrarArrayInt(arrayInt, longitud);
    return 0;
}
