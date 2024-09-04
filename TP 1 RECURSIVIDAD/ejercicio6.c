#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TP1_Recursividad.h"

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
        if (errno != 0 || *finptr != '\0') {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion auxiliar recursiva
void piso(char *chinos, const char *chino, int nivel) {
    if (nivel < 1) {
        return;
    } else {
        strcat(chinos, chino);
        piso(chinos, chino, nivel - 1);
    }
}

// funcion principal del ejercicio
char * reunionMafia(int nivel) {
    int chinosEnNivel = (nivel * 2) - 1; // calculo del número de chinos en todo el nivel
    int chinosPorLado = chinosEnNivel / 2; // como siempre hay uno al centro, calculo del numero de chinos por lado
    char chinoEntero[] = "(-.-)";
    char chinoIzq[] = "(-.";
    char chinoDer[] = ".-)";
    char* chinos = (char*)malloc((strlen(chinoEntero) + strlen(chinoIzq) * chinosPorLado + strlen(chinoDer) * chinosPorLado + 1) * sizeof(char));
    chinos[0] = '\0';
    piso(chinos, chinoIzq, chinosPorLado);
    piso(chinos, chinoEntero, 1);
    piso(chinos, chinoDer, chinosPorLado);
    return chinos;
}

int main() {
    int nivel = 0;
    printf("Ingrese el nivel para calcular la reunion de chinos (rango entre 1 y 600): ");
    nivel = leer_entero();
    while (nivel < 1 || nivel > 600) {
        printf("El nivel ingresado no pertenece al rango permitido. Reingrese el nivel: ");
        nivel = leer_entero();
    }

    char *chinos = reunionMafia(nivel);
    printf("Reunion de nivel %d: %s \n", nivel, chinos);
    printf("\n");

    free(chinos);
    return 0;
}
