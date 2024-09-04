#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "TP1_Recursividad.h"

#define TAM_MAX 100

// FUNCION TRIM PARA VALIDAR ESPACIOS (Validacion)
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

// FUNCION PARA LEER Y VALIDAR NUMEROS ENTEROS DEL TECLADO
int leer_entero() {
    char entrada[100];
    long numero;
    char *finptr;
    int valido = 0;

    while (!valido) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada) - 1] = '\0';
        strtrim(entrada);
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 10000000 || numero < -10000000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int)numero;
}

// FUNCION RECURSIVA AUXILIAR
void generarSubconjuntos(int conjunto[], int inicio, int longitud, int suma, int objetivo, int *subconj, int idx, int **resultado, int *numSubconjuntos) {
    if (inicio >= longitud) {
        // Si se alcanza el final del conjunto
        if (suma == objetivo && idx > 0) {
            // si la suma es igual al objetivo y el subconjunto no esta vacío, añadir el subconjunto a la lista de resultados
            resultado[*numSubconjuntos] = (int *)malloc((idx + 1) * sizeof(int));
            memcpy(resultado[*numSubconjuntos], subconj, idx * sizeof(int));
            resultado[*numSubconjuntos][idx] = 0; // marcar el final del subconjunto con un cero
            (*numSubconjuntos)++;
        }
        return;
    }

    // incluir el elemento actual en el subconjunto y llamar recursivamente
    subconj[idx] = conjunto[inicio];
    generarSubconjuntos(conjunto, inicio + 1, longitud, suma + conjunto[inicio], objetivo, subconj, idx + 1, resultado, numSubconjuntos);

    // llamar sin incluir el elemento actual en el subconjunto
    generarSubconjuntos(conjunto, inicio + 1, longitud, suma, objetivo, subconj, idx, resultado, numSubconjuntos);
}

// FUNCION PRINCIPAL
int **subconjuntosQueSumanN(int conjunto[], int n, int objetivo, int *numSubconjuntos) {
    // calculo el numero maximo de subconjuntos posibles (2^n)
    int maxSubconjuntos = 1 << n;
    int **resultado = (int **)malloc(maxSubconjuntos * sizeof(int *));
    int *subconj = (int *)malloc(n * sizeof(int));
    *numSubconjuntos = 0;
    generarSubconjuntos(conjunto, 0, n, 0, objetivo, subconj, 0, resultado, numSubconjuntos);
    free(subconj);
    return resultado;
}

int main() {
    int conjunto[TAM_MAX];
    int cantidad = 0;
    int tamano = 0;

    printf("[NUM OBJETIVO]\n");
    printf("El rango es entre -10.000.000 y 10.000.000\n");
    printf("Ingrese un numero entero. ");
    cantidad = leer_entero();

    printf("[INGRESO DE CONJUNTO]\n");
    printf("El rango es entre -10.000.000 y 10.000.000\n");
    while (true) { // inicio de un ciclo while que continuara hasta que se ingrese el caracter "*"
        if (tamano >= TAM_MAX) {
            printf("Se llego al tamano maximo del conjunto (%d elementos)\n", TAM_MAX);
            break;
        }
        printf("Ingrese un elemento del conjunto (o '*' para terminar). Elemento numero %d: ", tamano + 1);
        char entrada[100];
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strcmp(entrada, "*") == 0) {
            break;
        }

        // convertir la entrada a un numero entero
        char *endptr;
        long numero = strtol(entrada, &endptr, 10);
        // verificar si se ingreso un numero valido
        if (*endptr != '\0' || numero > 10000000 || numero < -10000000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            conjunto[tamano] = (int)numero;
            tamano++;
        }
    }

    if (tamano <= 0) {
        printf("\nCONJUNTO VACIO.\n");
    } else {
        printf("\nCONJUNTO CARGADO.\n");
        int numSubconjuntos;
        int **resultado = subconjuntosQueSumanN(conjunto, tamano, cantidad, &numSubconjuntos);

        // ACA SE MUESTRAN LOS SUBCONJUNTOS
        printf("Subconjuntos que suman %d:\n", cantidad);
        for (int i = 0; i < numSubconjuntos; i++) {
            int j = 0;
            printf("{");
            while (resultado[i][j] != 0) {
                printf("%d", resultado[i][j]);
                if (resultado[i][j + 1] != 0) {
                    printf(", ");
                }
                j++;
            }
            printf("}\n");
            free(resultado[i]);
        }
        free(resultado);
    }

    return 0;
}
