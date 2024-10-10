#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "colas.h"
#include "pilas.h"

// funcion que elimina los espacios de una cadena de char ingresada
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
            printf("Entrada invalida (rango entero de -100k a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion que rellena una cola por teclado
Cola rellenar_cola_por_teclado() {
    Cola cola = c_crear();
    int longitudCola = 0;
    printf("Ingrese la longitud de la cola (entre 1 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la cola, solo se cargaran hasta que se llene la misma.\n");
    longitudCola = leer_entero();
    while (longitudCola < 1 || longitudCola > 100000) {
        printf("Entrada invalida. Fuera del rango disponible para la cola. Reingrese el tamanio. ");
        longitudCola = leer_entero();
    }
    int i = 1;
    while (i <= longitudCola) {
        if (c_es_llena(cola)) {
            printf("La cola ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        printf("Ingrese el elemento %d (entre -100.000 y 100.000):\n", i);
        int ingreso = leer_entero();
        TipoElemento elemento = te_crear(ingreso);
        c_encolar(cola, elemento);
        i++;
    }
    return cola;
}

// 2. Resolver los siguientes puntos:
// a. Informar si un elemento dado se encuentra en la cola
bool c_ej2_existeclave(Cola c, int clave) {
    Cola cAux = c_crear();
    bool res = false;
    while (!c_es_vacia(c)) {
        TipoElemento ele = c_desencolar(c);
        if (ele->clave == clave) {res = true;}
        c_encolar(cAux, ele);
    }

    while(!c_es_vacia(cAux)) {
        c_encolar(c, c_desencolar(cAux));
    }
    return res;
}

// b. Agregar un nuevo elemento en una posicion dada (colarse)
Cola c_ej2_colarelemento(Cola c, int posicionordinal) {
    int i = 1;
    bool continuar = true;
    Cola cAux = c_crear();
    TipoElemento ele;
    printf("Ingrese el numero para agregar (colarse). ");
    int claveParaElemento = leer_entero();
    TipoElemento elementoAgregar = te_crear(claveParaElemento);
    while (continuar) {
        continuar = false;
        if (1 <= posicionordinal) {
            while (!c_es_vacia(c)) {
                ele = c_desencolar(c);
                if (posicionordinal == i){
                    c_encolar(cAux, elementoAgregar);
                }
                c_encolar(cAux, ele);
                i++;
            }
            if (posicionordinal == i) {c_encolar(cAux, elementoAgregar);}
            if (posicionordinal > i) {
                printf("Elemento fuera de rango. Reintentando...\n");
                continuar = true;
                i = 1;
            }

            while (!c_es_vacia(cAux)) {
                c_encolar(c, c_desencolar(cAux));
            }
        } else {
            printf("Elemento fuera de rango. Reintentando...\n");
            continuar = true;
            i = 1;
        }
    }
    return c;
}

// c. Dado un elemento sacarlo de la cola todas las veces que aparezca
Cola c_ej2_sacarelemento(Cola c, int clave) {
    Cola cAux = c_crear();
    Cola cSinElemento = c_crear();
    TipoElemento elemento;
    bool seEliminoAlgo = false;
    while (!c_es_vacia(c)) {
        elemento = c_desencolar(c);
        if (elemento->clave != clave) {
            seEliminoAlgo = true;
            c_encolar(cSinElemento, elemento);
        }
        c_encolar(cAux, elemento);
    }
    while (!c_es_vacia(cAux)) {
        c_encolar(c, c_desencolar(cAux));
    }
    if (!seEliminoAlgo) {
        return c;
    } else {
        return cSinElemento;
    }
}

// d. Contar los elementos de la cola
int c_ej2_contarelementos(Cola c) {
    Cola cAux = c_crear();
    int res = 0;
    while (!c_es_vacia(c)) {
        c_encolar(cAux, c_desencolar(c));
        res++;
    }
    while (!c_es_vacia(cAux)) {
        c_encolar(c, c_desencolar(cAux));
    }
    return res;
}

// e. Realizar una función que realice una copia de una cola
Cola c_ej2_copiar(Cola c) {
    Cola cAux = c_crear();
    Cola res = c_crear();
    while (!c_es_vacia(c)) {
        TipoElemento ele = c_desencolar(c);
        c_encolar(cAux, ele);
        c_encolar(res, ele);
    }
    while (!c_es_vacia(cAux)) {
        c_encolar(c, c_desencolar(cAux));
    }
    return res;
}

// f. Invertir del contenido de una cola sin destruir la cola original
Cola c_ej2_invertir(Cola c) {
    Cola cAux = c_crear();
    Cola res = c_crear();
    Pila P = p_crear();
    TipoElemento ultimo, ele;
    while (!c_es_vacia(c)) {
        ele = c_desencolar(c);
        c_encolar(cAux, ele);
        p_apilar(P, ele);
    }
    while(!p_es_vacia(P)) {
        c_encolar(res, p_desapilar(P));
    }
    while(!c_es_vacia(cAux)) {
        c_encolar(c, c_desencolar(cAux));
    }
    return res;
}

int main() {
    // INGRESO Y VALIDACION
    printf("[INGRESO COLA]\n");
    Cola cola = rellenar_cola_por_teclado();
    c_mostrar(cola);
    printf("\n");
    // a. Informar si un elemento dado se encuentra en la cola.
    printf("=== a. Informar si un elemento dado se encuentra en la cola.\n");
    printf("= Cola original: ");
    c_mostrar(cola);
    printf("Introduzca la clave a buscar. ");
    int clave = leer_entero();
    if (c_ej2_existeclave(cola, clave)) {
        printf("La clave buscada existe.\n");
    } else {
        printf("La clave buscada NO existe.\n");
    }
    // b. Agregar un nuevo elemento en una posicion dada (colarse)
    printf("=== b. Agregar un nuevo elemento en una posicion dada (colarse).\n");
    printf("= Cola original: ");
    c_mostrar(cola);
    if (!c_es_llena(cola)) {
        printf("Introduzca la posicion ordinal para colarse. ");
        Cola copiaCola = c_ej2_copiar(cola);
        int posColar = leer_entero();
        while (posColar < 1 || posColar > c_ej2_contarelementos(copiaCola)) {
            printf("La posicion para agregar es invalida. Reingrese la posicion. ");
            posColar = leer_entero();
        }
        c_ej2_colarelemento(copiaCola, posColar);
        printf("= Cola con elemento colado: ");
        c_mostrar(copiaCola);
    } else {
        printf("\nLa cola esta llena. No se podra colar el elemento.\n");
    }
    // c. Dado un elemento sacarlo de la cola todas las veces que aparezca.
    printf("=== c. Dado un elemento sacarlo de la cola todas las veces que aparezca.\n");
    printf("= Cola original: ");
    c_mostrar(cola);
    if (!c_es_vacia(cola)) {
        printf("Introduzca la clave a eliminar (se sacaran todas sus apariciones). ");
        int claveSacar = leer_entero();
        printf("= Cola sin la clave: ");
        c_mostrar(c_ej2_sacarelemento(cola, claveSacar));
    } else {
        printf("\nLa cola esta vacia. No se podran eliminar elementos.\n");
    }
    // d. Contar los elementos de la cola.
    printf("=== d. Contar los elementos de la cola.\n");
    printf("= Cola original: ");
    c_mostrar(cola);
    if (!c_es_vacia(cola)) {
        printf("La longitud de la cola es %d\n", c_ej2_contarelementos(cola));
    } else {
        printf("La cola esta vacia.\n");
    }
    // e. Realizar una función que realice una copia de una cola.
    printf("=== e. Realizar una función que realice una copia de una cola.\n");
    printf("= Cola original: ");
    c_mostrar(cola);
    printf("= Copia de la cola: ");
    c_mostrar(c_ej2_copiar(cola));
    // f. Invertir el contenido de una cola sin destruir la cola original.
    printf("=== f. Invertir el contenido de una cola sin destruir la cola original.\n");
    printf("= Cola original: ");
    c_mostrar(cola);
    printf("= Cola invertida: ");
    c_mostrar(c_ej2_invertir(cola));
    return 0;
}
