#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "listas.h"

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
        printf("Ingrese un numero entero: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        if (entrada[0] == '\0') {
            printf("Entrada invalida. Intentelo de nuevo.\n");
            continue;
        }
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 100000 || numero < -100000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion para leer un flotante por teclado (validacion)
float leer_flotante() {
    char entrada[100];
    float numero;
    char *finptr;
    int valido = 0;

    while (!valido) {
        printf("Ingrese un numero flotante (-100k a 100k): ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        if (entrada[0] == '\0') {
            printf("Entrada invalida. Intentelo de nuevo.\n");
            continue;
        }
        errno = 0;
        numero = strtof(entrada, &finptr);
        if (errno != 0 || *finptr != '\0' || numero > 100000 || numero < -100000) {
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return numero;
}

// funcion para leer un entero por teclado limitado por el minimo y maximo grado disponible (validacion)
int leer_grado() {
    int grado = grado = leer_entero();
    while ((grado < 0) || (grado > 9)) {
        printf("El grado del polinomio no puede ser negativo o mayor a 9. Intentelo de nuevo.\n");
        grado = leer_entero();
    }
    return grado;
}

// funcion para leer un flotante por teclado que no pueda ser negativo o 0 (validacion)
float leer_intervalo() {
    float intervalo = -1;
    while (intervalo <= 0) {
        intervalo = leer_flotante();
        if (intervalo < 0 || intervalo > 500) {
            printf("El intervalo no puede ser negativo, 0, o mayor a 500. Intentelo de nuevo.\n");
        }
    }
    return intervalo;
}

// funcion para rellenar lista por teclado
Lista rellenar_lista_teclado(Lista lista) {
    int grado = 0;
    float entrada = 0;
    printf("Ingrese el grado del polinomio (rango de 0 a 9): ");
    grado = leer_grado();
    for (int i = grado; i >= 0; i--) {
        if (i == 0) {
            printf("Ingrese el coeficiente del polinomio para el termino independiente (grado 0). ");
        } else {
            printf("Ingrese el coeficiente del polinomio para el grado %d. ", i);
        }
        entrada = leer_flotante();
        char *str_valor = (char*) malloc(sizeof(char) * 10);
        sprintf(str_valor, "%f", entrada);
        TipoElemento elemento = te_crear_con_valor(i, str_valor);
        l_agregar(lista, elemento);
    }
    return lista;
}

// funcion que muestra un polinomio basado en la lista ingresada
void mostrar_polinomio(Lista lista) {
    printf("------------------ \n");
    if (l_es_vacia(lista)) {
        printf("El polinomio esta vacio.\n");
        return;
    } else {
        float valor = 0;
        Iterador iter = iterador(lista);
        printf("El polinomio ingresado es: ");
        while (hay_siguiente(iter)) {
            TipoElemento elemento = siguiente(iter);
            valor = atof(elemento->valor);
            if (elemento->clave != 0) {
                printf("%.2fX^%d", valor, elemento->clave);
                printf(" + ");
            } else {
                printf("%.2f", valor);
            }
        }
        printf("\n ------------------ \n");
    }
}

// funcion para calcular cuando da un numero flotante reemplazado en el polinomio
float calcular_polinomio(Lista lista, float x) {
    int clave = 0;
    float resultado = 0;
    float valor = 0;
    Iterador iter = iterador(lista);
    while (hay_siguiente(iter)) {
        TipoElemento elemento = siguiente(iter);
        valor = atof(elemento->valor);
        clave = elemento->clave;
        resultado += valor * pow(x, clave);
    }
    printf("El resultado del polinomio con f(%.2f) es: %.2f\n", x, resultado);
    return resultado;
}

// funcion para chequear si se supera el limite de tamaño de la lista
bool supera_limite_lista(float minX, float maxX, float intervaloI) {
    int contadorElementos = 0;
    bool supera = false;
    while (minX <= maxX && !supera) {
        minX += intervaloI;
        contadorElementos++;
        if (contadorElementos < 0) {
            supera = true;
        }
    }
    return supera;
}

// funcion que segun el polinomio, el minimo y el maximo, te devuelte una lista con los saltos de intervalo
Lista calcular_intervalo(Lista lista, float minX, float maxX, float intervaloI) {
    if (!supera_limite_lista(minX, maxX, intervaloI)) {
        Lista listaResultado = l_crear();
        int claveNuevaLista = 1;

        while (minX <= maxX) {
            if (l_es_llena(listaResultado)) {
                printf("La lista ha alcanzado su limite maximo. No se pueden agregar ni mostrar mas elementos.\n");
                break;
            }

            float resultado = calcular_polinomio(lista, minX);
            char *str_valor = (char*) malloc(sizeof(char) * 10);
            sprintf(str_valor, "%f", resultado);
            TipoElemento elemento = te_crear_con_valor(claveNuevaLista, str_valor);
            l_agregar(listaResultado, elemento);
            minX += intervaloI;
            claveNuevaLista++;
        }
        return listaResultado;
    } else {
        printf("Debido a que la cantidad de elementos supera al tamano maximo de la lista, no se puede completar la accion.\n");
        return NULL;
    }
}

int main() {
    // Creación y seteo de la lista
    Lista lista = l_crear();
    lista = rellenar_lista_teclado(lista);
    mostrar_polinomio(lista);

    // Punto 5A
    float x = 0;
    printf("Ingrese el valor de X: ");
    x = leer_flotante();
    calcular_polinomio(lista, x);
    printf("------------------\n");

    // Punto 5B
    float minX = 999;
    float maxX = 0;
    float intervaloI = 0;
    printf("--- INTERVALO ---\n");
    while (minX > maxX) {
        printf("Recuerde que el valor minimo de X debe ser menor al valor maximo de X.\n");
        printf("Ingrese el valor MINIMO de X: ");
        minX = leer_flotante();
        printf("Ingrese el valor MAXIMO de X: ");
        maxX = leer_flotante();
    }
    printf("Ingrese el valor del intervalo I: ");
    intervaloI = leer_intervalo();
    printf("... \n");
    Lista listaIntervalo = calcular_intervalo(lista, minX, maxX, intervaloI);
    printf("------------------ \n");
    return 0;
}
