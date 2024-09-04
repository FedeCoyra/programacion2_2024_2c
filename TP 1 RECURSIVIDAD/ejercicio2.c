#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "TP1_Recursividad.h"

// Funcion recursiva
int producto_sucesivo(int m, int n, int total) {
    if (n == 0) {
        return total;
    } else {
        if (n < 0) {
            n += 1;
            total -= m;
        } else {
            n -= 1;
            total += m;
        }
        producto_sucesivo(m, n, total);
    }
}

// Funcion que retorna el producto sucesivo entre dos numeros
int producto(int m, int n) {
    return producto_sucesivo(m, n, 0);
}

// Funcion que elimina espacios en blanco de una cadena
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

// Funcion para leer un entero por teclado (validacion)
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
            printf("Entrada invalida. Intentelo nuevamente.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

int main() {
    int m, n, total;
    printf("Ingrese dos valores (M y N) para calcular su producto sucesivo \n");
    printf("Rango entre -10.000 y 10.000\n");
    printf("(Se tomara 0 input vacio) \n ");
    printf("Ingrese el numero entero M: ");
    m = leer_entero();
    printf("Ingrese el numero entero N: ");
    n = leer_entero();

    total = producto(m, n);
    printf("El producto sucesivo entre %d y %d es %d\n", m, n, total);
    return 0;
}
