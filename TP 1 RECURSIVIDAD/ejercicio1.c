#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "TP1_Recursividad.h"

const int TAM_MAX = 100;
const int TAM_MAX_AUX = 200;

// Palabra es palindromo ? de manera recursiva
bool palindromoRecursivo(char *cadena, int principio, int final) {
    if (cadena[principio] != cadena[final]) { // Caso base
        return false;
    } else {
        if (final <= principio) { // Caso base
            return true;
        } else {
            palindromoRecursivo(cadena, ++principio, --final); // Caso recursivo
        }
    }
}

// Funcion para saber si una palabra es palindromo
bool palindromo(char *cadena) {
    int principio = 0;
    int final = strlen(cadena) - 1;
    return palindromoRecursivo(cadena, principio, final);
}

int main() {
    char cadena[TAM_MAX + 1];
    char cadenaAux[TAM_MAX_AUX + 1];
    printf("ES O NO PALINDROMO? \n");
    printf("Ingrese una cadena de caracteres: ");
    fgets(cadenaAux, sizeof(cadenaAux), stdin);
    cadenaAux[strlen(cadenaAux)-1] = '\0'; // Elimina el caracter de nueva linea si existe

    // Validacion para que no supere el tamaño maximo
    while (strlen(cadenaAux) > TAM_MAX) {
        memset(cadenaAux, '\0', sizeof(cadenaAux)); // inicializo la cadena
        printf("La cadena tiene mas de %d caracteres, ingrese una cadena mas corta. \n", TAM_MAX);
        printf("Ingrese una cadena: ");
        fgets(cadenaAux, sizeof(cadenaAux), stdin);
        cadenaAux[strlen(cadenaAux)-1] = '\0';;
    }


    strcpy(cadena, cadenaAux); // Cadena_destino, Cadena_origen

    // Se pasa a tolower para la comparacion, discriminando mayusculas y minusculas
    for (int i = 0; (i < strlen(cadena)); i++){
        cadena[i] = tolower(cadena[i]);
    }

    // No se considera palindromo si es vacia
    if ((strlen(cadena)) == 0) {
        printf("Cadena vacia.");
    } else {
        if (palindromo(cadena)) {
            printf("Es palindromo.");
        } else {
            printf("No es palindromo.");
        }
    }
    return 0;
}
