#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TP1_Recursividad.h"

const int TAM_MAX = 200;

// Funcion que retorna - o _
char valorDeOnda(char valor) {
    if (toupper(valor) == 'L') {
        return '_';
    } else {
        return '-';
    }
}

// Funcion que retorna una onda
void generadorDeOnda(char *cadena, int *posicion, char *onda, int *posicionOnda) {
    if (*posicion == strlen(cadena) - 1) {
        onda[*posicionOnda] = valorDeOnda(cadena[*posicion]);
        *posicionOnda = *posicionOnda + 1;
        return;
    } else {
        onda[*posicionOnda] = valorDeOnda(cadena[*posicion]);
        if (valorDeOnda(cadena[*posicion + 1]) != valorDeOnda(cadena[*posicion])) {
            onda[*posicionOnda + 1] = '|';
            *posicionOnda = *posicionOnda + 2;
        } else {
            *posicionOnda = *posicionOnda + 1;
        }
        *posicion = *posicion + 1;
        generadorDeOnda(cadena, posicion, onda, posicionOnda);
    }
}

char * ondaDigital(char seniales[]) {
    int posicion = 0;
    int posicionOnda = 0;
    char * onda = calloc((TAM_MAX + 1), sizeof(char));
    memset(onda, 0, sizeof(onda));
    generadorDeOnda(seniales, &posicion, onda, &posicionOnda);
    return onda;
}

int main() {
    char cadena[TAM_MAX + 1];
    int valido = 0;

    while (!valido) {
        printf("Ingrese la cadena de onda (max 200 caracteres): ");
        scanf(" %201[^\n]", cadena);
        int i;
        for (i = 0; i < strlen(cadena); i++) {
            if (toupper(cadena[i]) != 'L' && toupper(cadena[i]) != 'H') {
                printf("La cadena ingresada no es valida, ingrese L y/o H (sin espacios).\n");
                break;
            }
        }
        if (i == strlen(cadena)) {
            valido = 1;
        }
    }
    if (strlen(cadena) > TAM_MAX) {
        printf("La cadena ingresada sobrepaso el limite maximo permitido por el programa. No se incluiran los caracteres sobrantes a la onda.\n");
    }
    printf("La cadena ingresada es: %s\n", cadena);
    char *onda = ondaDigital(cadena);
    printf("La onda resultante es: %s", onda);
    return 0;
}
