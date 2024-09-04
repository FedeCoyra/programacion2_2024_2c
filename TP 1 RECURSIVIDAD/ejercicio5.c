#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "TP1_Recursividad.h"

char* ponerPuntosDeMil(char* cadena, char *numero,int contador, int index, int negativo);
void strtrim(char *cadena);

const int TAM_MAX = 50;
const int TAM_MAX_AUX = 100;

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

// funcion recursiva que invierte una cadena
void invertirCadena(char *cadena, int inicio, int fin) {
    if (inicio >= fin) { // caso base
        return;
    }
    char temp = cadena[inicio];
    cadena[inicio] = cadena[fin];
    cadena[fin] = temp;

    // caso recursivo
    invertirCadena(cadena, inicio + 1, fin - 1);
}

// funcion que saca los ceros de la izquierda de un char
void sacarCerosAdelante(char *cadena) {
    if (cadena == NULL || *cadena == '\0' || (strlen(cadena) == 1 && *cadena == '0')) {
        return;
    }
    int indicePrimerDigito = 0;
    while (cadena[indicePrimerDigito] == '0') {
        indicePrimerDigito++;
    }
    if (indicePrimerDigito > 0) {
        memmove(cadena, cadena + indicePrimerDigito, strlen(cadena) - indicePrimerDigito + 1);
    }
}

// funcion que le agrega a un numero sus puntos de mil
char* ponerPuntosDeMil(char* cadena, char *numero, int contador, int index, int negativo){
    if (index == negativo){
        char c[] = " ";
        c[0] = numero[index];
        strcat(cadena, c);
        return cadena;
    } else{
        if (contador == 2){
            char c[] = " ";
            c[0] = numero[index];
            strcat(cadena, c);
            strcat(cadena, ".");
            contador = 0;
            index = index - 1;
            ponerPuntosDeMil(cadena, numero,contador,index, negativo);
        } else{
            contador = contador + 1;
            char c[] = " ";
            c[0] = numero[index];
            strcat(cadena, c);
            index = index - 1;
            ponerPuntosDeMil(cadena, numero,contador,index, negativo);
        }
    }
}

char * agregarSeparadorMiles(char numero[]) {
    char cRetorno[150]; // cadena retorno
    memset(cRetorno, 0, 150); // inicializo la cadenaRetorno
    char * c = calloc(150, sizeof(char));
    if (numero[0] == '-') {
        c = ponerPuntosDeMil(cRetorno, numero,0,(strlen(numero) - 1), 1);
        strcat(c, "-");
    } else {
        c = ponerPuntosDeMil(cRetorno, numero,0,(strlen(numero) - 1), 0);
    }
    invertirCadena(c, 0, (strlen(c) - 1));
    return c;
}

int main(){
    char numeroIngresado[TAM_MAX + 1];
    char numeroIngresadoAux[TAM_MAX_AUX + 1];
    bool noEsValido = true;
    while (noEsValido) {
        printf("Ingresar numero entero: ");
        fgets(numeroIngresadoAux, sizeof(numeroIngresadoAux), stdin);
        if((strlen(numeroIngresadoAux) != 0) && (numeroIngresadoAux[strlen(numeroIngresadoAux)-1] == '\n')){
            numeroIngresadoAux[strlen(numeroIngresadoAux) - 1] = '\0';
        }

        strtrim(numeroIngresadoAux);
        sacarCerosAdelante(numeroIngresadoAux);
        if(numeroIngresadoAux[0] == '-' || isdigit(numeroIngresadoAux[0])) {
            for (int i = 1; i < strlen(numeroIngresadoAux); i++) {
                if (!isdigit(numeroIngresadoAux[i])){
                    noEsValido = false;
                }
            }
            noEsValido = !noEsValido;
        }
    }

    // validado de que no supere el tamaño maximo
    while (strlen(numeroIngresadoAux) > TAM_MAX) {
        memset(numeroIngresadoAux, '\0', sizeof(numeroIngresadoAux)); // inicializo la cadena
        printf("El numero tiene mas de %d caracteres, ingrese un numero mas corto. ", TAM_MAX);
        bool noEsValido = true;
        while (noEsValido) {
            printf("Ingresar numero entero: ");
            fgets(numeroIngresadoAux, sizeof(numeroIngresadoAux), stdin);
            if((strlen(numeroIngresadoAux) != 0) && (numeroIngresadoAux[strlen(numeroIngresadoAux)-1] == '\n')){
                numeroIngresadoAux[strlen(numeroIngresadoAux) - 1] = '\0';
            }

            strtrim(numeroIngresadoAux);
            sacarCerosAdelante(numeroIngresadoAux);
            if(numeroIngresadoAux[0] == '-' || isdigit(numeroIngresadoAux[0])) {
                for (int i = 1; i < strlen(numeroIngresadoAux); i++) {
                    if (!isdigit(numeroIngresadoAux[i])){
                        noEsValido = false;
                    }
                }
                noEsValido = !noEsValido;
            }
        }
    }
    // Si es valido y llega aca, se le asigna cadenaAux a cadena
    strcpy(numeroIngresado, numeroIngresadoAux); // cadena_destino, cadena_origen

    char *c = agregarSeparadorMiles(numeroIngresado);
    int len = strlen(c);

    printf("%s\n", c);
    free(c);
    return 0;
}
