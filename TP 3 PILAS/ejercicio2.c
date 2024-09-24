#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include "pilas.h"

// Funcion que intercambia una pila auxiliar a una pila
void intercambiar(Pila pila, Pila pAux) {
    TipoElemento elemento;
    while (!p_es_vacia(pAux)){
        elemento = p_desapilar(pAux);
        p_apilar(pila, elemento);
    }
}

// Funcion que elimina los espacios de una cadena de char ingresada
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

// Funcion para leer un entero por teclado (VALIDACION)
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
            printf("Entrada invalida (rango de -100k a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion que copia una pila sin alterar la original
Pila copiar_pila(Pila pilaOriginal) {
    Pila pilaAuxiliar = p_crear();
    Pila pilaCopia = p_crear();
    while (!p_es_vacia(pilaOriginal)) {
        TipoElemento elemento = p_desapilar(pilaOriginal);
        p_apilar(pilaAuxiliar, elemento);
    }
    while (!p_es_vacia(pilaAuxiliar)) {
        TipoElemento elemento = p_desapilar(pilaAuxiliar);
        p_apilar(pilaOriginal, elemento);
        p_apilar(pilaCopia, elemento);
    }
    return pilaCopia;
}

// 2. Dada una pila cargada con valores al azar realizar los siguientes ejercicios:
// f. Contar los elementos de la pila.
int p_ej2_cantidadelementos(Pila p) {
    Pila Paux = p_crear();
    int cantidad = 0;
    // cuenta los elementos desapilando la pila mientras guarda los elementos en una pila auxiliar
    while (!p_es_vacia(p)) {
        p_apilar(Paux, p_desapilar(p));
        cantidad++;
    }
    // vuelve a apilar los elementos de la pila original
    while(!p_es_vacia(Paux)) {
        p_apilar(p, p_desapilar(Paux));
    }
    return cantidad;
}

// a. Buscar una clave y determinar si existe en la Pila (sin perder la pila).
bool p_ej2_existeclave(Pila p, int clave) {
    if (p_es_vacia(p)) {
        return false;
    }

    Pila Paux = p_crear();
    TipoElemento elemento;
    bool res = false;

    while (!p_es_vacia(p) && !res) {
        elemento = p_desapilar(p);
        if (clave == elemento->clave){
            res = true;
        }
        p_apilar(Paux, elemento);
    }

    while (!p_es_vacia(Paux)) {
        p_apilar(p, p_desapilar(Paux));
    }
    return res;
}

/* b. Colocar en una posición ordinal determinada, recibida por parámetro, un
nuevo elemento (Insertar un elemento nuevo). */
Pila p_ej2_colocarelemento(Pila p, int posicionordinal) {
    Pila nuevaPila = copiar_pila(p);

    if (p_es_llena(p)){
        printf("La pila esta llena, por tanto, no puede insertarse el elemento.\n");
        return p;
    }

    while (posicionordinal > p_ej2_cantidadelementos(p) || posicionordinal < 1) {
        printf("La posicion debe respetar el rango de la pila. Ingrese una nueva posicion: ");
        posicionordinal = leer_entero();
    }

    int clavePorInsertar = leer_entero();
    TipoElemento elementoInsertar = te_crear(clavePorInsertar);

    if (posicionordinal == 1) {
        p_apilar(nuevaPila, elementoInsertar);
        return nuevaPila;
    }

    Pila pilaAux = p_crear();
    while (!p_es_vacia(nuevaPila)) {
        p_apilar(pilaAux, p_desapilar(nuevaPila));
    }

    int contador = p_ej2_cantidadelementos(pilaAux);
    while (!p_es_vacia(pilaAux)) {
        if (contador == posicionordinal) {
            TipoElemento elementoAux = p_desapilar(pilaAux);
            p_apilar(nuevaPila, elementoAux);
            p_apilar(nuevaPila, elementoInsertar);
        }
        p_apilar(nuevaPila, p_desapilar(pilaAux));
        --contador;
    }
    return nuevaPila;
}

/* c. Eliminar de una pila un elemento dado (primera ocurrencia encontrada por la
clave). */
Pila p_ej2_eliminarclave(Pila p, int clave) {
    Pila nuevaPila = copiar_pila(p);

    if (p_es_vacia(nuevaPila)) {
        printf("La pila esta vacia, por tanto, no es posible eliminar una clave.\n");
        return false;
    }

    if (!p_ej2_existeclave(nuevaPila, clave)) {
        printf("El elemento a eliminar no se encuentra en la pila.\n");
    }
    Pila pAux = p_crear();
    TipoElemento X;
    bool yaBorrado = false;
    while (!p_es_vacia(nuevaPila)) {
        X = p_desapilar(nuevaPila);
        if (X -> clave != clave || yaBorrado){
            p_apilar(pAux, X);
        } else {
            yaBorrado = true;
        }
    }
    intercambiar(nuevaPila, pAux);
    free(pAux);
    return nuevaPila;
}

/* d. Intercambiar los valores de 2 posiciones ordinales de la pila, por ejemplo la
2da con la 4ta. */

Pila p_ej2_intercambiarposiciones(Pila p, int pos1, int pos2) {
    Pila nuevaPila = copiar_pila(p);

    if (p_es_vacia(nuevaPila)) return nuevaPila;
    if (pos2 == pos1) {
        return nuevaPila;
    } else {
        Pila pAux = p_crear();
        TipoElemento AuxPosMenor, AuxPosMayor, X;
        int i = 1, longitudPila = p_ej2_cantidadelementos(nuevaPila);
        while (pos1 > pos2 || pos1 < 1 || pos2 < 1 || pos1 > longitudPila || pos2 > longitudPila) {
            printf("La posicion menor debe ser menor o igual a la mayor.\n");
            printf("Las posiciones deben respetar el rango de la pila (mayor a 0, menor que la cantidad maxima).\n");
            printf("Reingrese la primera posicion: ");
            pos1 = leer_entero();
            printf("Reingrese la segunda posicion: ");
            pos2 = leer_entero();
        }
        bool listoParaIntercambiar = false;
        while(!p_es_vacia(nuevaPila) && !listoParaIntercambiar && i <= longitudPila){
            if (i == pos1) {
                AuxPosMenor = p_desapilar(nuevaPila);
            } else if (i == pos2) {
                AuxPosMayor = p_desapilar(nuevaPila);
                listoParaIntercambiar = true;
            } else {
                X = p_desapilar(nuevaPila);
                p_apilar(pAux, X);
            }
            i++;
        }
        bool ambosIntercambiados = false;
        while(!p_es_vacia(pAux) || !ambosIntercambiados){
            if (i == pos2 + 1)
                p_apilar(nuevaPila, AuxPosMenor);
            else if (i == pos1 + 1){
                p_apilar(nuevaPila, AuxPosMayor);
                ambosIntercambiados = true;
            } else {
                X = p_desapilar(pAux);
                p_apilar(nuevaPila, X);
            }
            i--;
            }
        free(pAux);
        return nuevaPila;
    }
}

// e. Duplicar el contenido de una pila.
Pila p_ej2_duplicar(Pila p) {
    Pila nuevaPila = copiar_pila(p);

    Pila Paux = p_crear();
    TipoElemento elemento;
    while (!p_es_vacia(nuevaPila)) {
        elemento = p_desapilar(nuevaPila);
        elemento->clave = elemento->clave*2;
        p_apilar(Paux, elemento);
    }

    while (!p_es_vacia(Paux)) {
        p_apilar(nuevaPila, p_desapilar(Paux));
    }
    return nuevaPila;
}

// funcion que pide uan pila y la rellena aleatoriamente
void cargar_random(Pila P) {
    srand(time(NULL));
    for (int i = 0; i <= ((10 / 2) - 1); i++) {
        p_apilar(P, te_crear(rand()%100));
    }
}

Pila rellenar_pila_por_teclado() {
    Pila pila = p_crear();
    int longitudPila = 0;
    printf("Ingrese la longitud de la pila (entre 1 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    longitudPila = leer_entero();
    while (longitudPila < 1 || longitudPila > 100000) {
        printf("Entrada invalida. Fuera del rango disponible para la pila. Reingrese el tamanio. ");
        longitudPila = leer_entero();
    }
    int i = 1;
    while (i <= longitudPila) {
        if (p_es_llena(pila)) {
            printf("La pila ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        printf("Ingrese el elemento %d (entre -100.000 y 100.000):\n", i);
        int ingreso = leer_entero();
        TipoElemento elemento = te_crear(ingreso);
        p_apilar(pila, elemento);
        i++;
    }
    return pila;
}

int mostrar_menu() {
    int opcion;
    printf("========= MENU EJERCICIO 2 =========\n");
    printf("Seleccione una opcion:\n");
    printf("1. Cargar pila aleatoriamente\n");
    printf("2. Cargar pila manualmente\n");
    printf("Opcion: ");
    opcion = leer_entero();
    while (opcion < 1 || opcion > 2) {
        printf("Opcion no valida. Ingrese una opcion valida (1 o 2): ");
        opcion = leer_entero();
    }
    return opcion;
}

int main() {
    // Mostrar menu y seleccionar opcion
    int opcion = mostrar_menu();
    Pila P = p_crear();

    // Cargar la pila segun la opcion seleccionada
    if (opcion == 1) {
        printf("[PILA GENERADA ALEATORIAMENTE]\n");
        cargar_random(P);
    } else if (opcion == 2) {
        printf("[PILA GENERADA MANUALMENTE]\n");
        P = rellenar_pila_por_teclado();
    }

    // Mostrar la pila despues de cargarla
    p_mostrar(P);

    // Operaciones sobre la pila
    printf("Todas las operaciones se hacen sobre la pila original (sin perderla).\n");
    printf("\n=========================\n");

    // a. Buscar un numero en la pila
    printf("\n=== a. Ingrese un numero a buscar: ");
    int n = leer_entero();
    if (p_ej2_existeclave(P, n)) {
        printf("El numero %d esta en la pila\n", n);
    } else {
        printf("El numero %d no esta en la pila\n", n);
    }

    // b. Insertar un numero en una posicion especifica
    printf("\n=== b. Insertar un numero: \n");
    printf("EL TOPE (pos. ord. 1) ES %d\n", p_tope(P)->clave);
    printf("|   Indique una posicion: ");
    int pos = leer_entero();
    p_mostrar(p_ej2_colocarelemento(P, pos));

    // c. Eliminar un número especifico de la pila
    printf("\n=== c. Eliminar un numero especifico: ");
    int eli = leer_entero();
    p_mostrar(p_ej2_eliminarclave(P, eli));

    // d. Intercambiar dos posiciones de la pila
    printf("\n=== d. Intercambiar elementos (la 1ra posicion debe ser menor a la 2da)\n");
    printf("|   Indique la 1ra posicion: ");
    int n1 = leer_entero();
    printf("|   Indique la 2da posicion: ");
    int n2 = leer_entero();
    p_mostrar(p_ej2_intercambiarposiciones(P, n1, n2));

    // e. Duplicar cada elemento de la pila
    printf("\n=== e. Duplicar cada elemento de la pila\n");
    p_mostrar(p_ej2_duplicar(P));

    // f. Contar los elementos de la pila
    printf("\n=== f. Cantidad de elementos de la pila: %d elementos\n", p_ej2_cantidadelementos(P));

    return 0;
}
