#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "TP1_Recursividad.h"

// Funcion a la que se le ingresa un numero entero y retorna un booleano dependiendo si es divisible por 7
bool divisiblePor7 (int n) {
    if (n < 70 && n > -70) {
        return (n % 7 == 0);
    }
    int resultado = (n / 10) - (n % 10) * 2;
    return divisiblePor7(resultado);
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
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 10000000 || numero < -10000000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

void main(){
    int n;
    printf("Ingrese un valor entero para verificar si es divisible por 7 (si el ingreso es nulo, se asumira el 0) (MAX 10M - MIN -10M): ");
    n = leer_entero();
    if (divisiblePor7(n)) {
        printf("El numero %d es divisible por 7", n);
    } else {
        printf("El numero %d NO es divisible por 7", n);
    }
}
