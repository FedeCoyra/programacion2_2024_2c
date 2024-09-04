#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include "TP1_Recursividad.h"

// funcion principal del ejercicio
float division (int m, int n) {
    if (m == n) return 1; // los numeros iguales divididos entre si dan 1
    else if (m < n) return round(((float)m/n)*10000)/10000; // la division por un numero mayor que el dividendo devuelve una fraccion
    else if (m > n){ // si el dividendo es mayor al divisor retorna 1 + la misma funcion con m = m - n
        if (n > 0) return 1 + division(m - n, n);
        else if(n < 0) return - 1 + division(m + n, n);
    }
}

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
    memmove(cadena, comienzoDeCadena, finalDeCadena - comienzoDeCadena + 2);
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
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 10000 || numero < -10000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion para leer un entero sin cero por teclado (validacion)
int leer_entero_sin_cero() {
    char entrada[100];
    long numero;
    char *finptr;
    int valido = 0;

    while (!valido) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero == 0 || numero > 10000 || numero < -10000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

void main(){
    int m, n;
    printf("Ingrese dos valores (M y N) para calcular su division con restas sucesivas \n");
    printf("Rango entre -10.000 y 10.000\n");
    printf("Ingrese el numero M (0 si se ingresa vacio): ");
    m = leer_entero();
    printf("Ingrese el numero N (no se admite el cero): ");
    n = leer_entero_sin_cero();
    printf("El cociente de %d y %d es %0.4f\n", m, n, division(m, n));
}
