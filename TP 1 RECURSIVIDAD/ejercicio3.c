#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "TP1_Recursividad.h"

// Funcion que calcula el nivel de la Serie de Fibonacci
int terminoSerieFibonacci (int k) {
    if (k <= 0) return 1; // caso base
    else if (k == 1) return 1;
    else return terminoSerieFibonacci(k - 1) + terminoSerieFibonacci(k - 2); // caso recursivo
}

// Funcion que elimina espacios en blanco de una cadena (validacion)
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

// Funcion para leer un entero positivo por teclado (validacion)
int leer_entero_positivo_menor_40() {
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
        if (errno != 0 || *finptr != '\0' || numero < 0 || numero > 40) {
            printf("Entrada invalida. Intentelo de nuevo: ");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

int main() {
    int num;
    printf("Ingrese un numero entero positivo (se tomara 0 input vacio) (maximo 40): ");
    num = leer_entero_positivo_menor_40();
    printf("El numero pedido de la Serie de Fibonacci es %d", terminoSerieFibonacci(num));
}
