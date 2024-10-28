#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol-binario.h"
#include "tipo_elemento.h"
#include "nodo.h"
#include "listas.h"
#include "pilas.h"

// funcion que muestra arbol en pre orden
void mostrar_arbol_pre_ord(NodoArbol actual) {
    TipoElemento x;
    if (a_es_rama_nula(actual))
        printf(".");
    else {
        x = n_recuperar(actual);
        printf("%d ", x->clave);
        mostrar_arbol_pre_ord(n_hijoizquierdo(actual));
        mostrar_arbol_pre_ord(n_hijoderecho(actual));
    }
}

// funcion que convierte, si se puede, una entrada arr de chars a entero
bool conversionEntero(char *string, int *nro, int len) {
    int i = 0;
    // Contar la cantidad de espacios.
    while(isspace(string[i]))
        i++;
    // Controlar cadena vacia.
    if (len == i) return false;

    char * buffer = malloc(sizeof(char)*len);
    int indiceEntero = 0;

    // Controlar si es un numero negativo.
    if (string[i] == '-'){
        buffer[indiceEntero] = '-';
        indiceEntero++;
        i++;

        if (!isdigit(string[i])) return false;
    }

    // Leer los digitos.
    while (i < len && !isspace(string[i])){
        if (!isdigit(string[i])) return false;
        buffer[indiceEntero] = string[i];
        indiceEntero++;
        i++;
    }

    // Agregar el caracter nulo al final del string.
    buffer[indiceEntero] = '\0';

    // Termino de recorrer el string.
    while (isspace(string[i]))
        i++;

    // Si hay mas para recorrer y no son blancos, el string contiene otros caracteres.
    if (string[i] != '\0') return false;

    // Convierto el string a un entero.
    *nro = atoi(buffer);
    return true;
}

// funcion que detecta un "." y retorna un bool dependiendo si lo encuentra
bool detectarPunto(char *string, int *nro, int len) {
    int i = 0;
    while(isspace(string[i]))
        i++;

    if (len == i) return false;
    if (string[i] != '.') return false;
    i++;
    while (string[i] == ' ') {
      i++;
    };
    if (string[i] != '\n') return false;
    return true;
}

// funcion que valida un numero entero
bool pedirNodoN(int *nro, int tamanio) {
    bool conversionCorrecta = true;
    do {
        char * bufferNro = malloc(sizeof(char) * tamanio);
        fgets(bufferNro, tamanio, stdin);
        conversionCorrecta = conversionEntero(bufferNro, nro, tamanio);
        if (!conversionCorrecta){
            if (detectarPunto(bufferNro, nro, tamanio)) {
              return false;
            }
            printf("El numero es invalido, revisa los requerimientos\n");
            printf("Ingrese otro numero: ");
            fflush(stdin);
        }
    } while (!conversionCorrecta);
    return true;
}

// funcion que pide y rellena con datos un arbol binario
void pedirArbol (ArbolBinario arbol) {
    int clave;
    printf("Ingrese raiz: ");
    bool pedido = pedirNodoN(&clave, 11);
    if (!pedido) {
    printf("Arbol vacio \n");
    } else {
    Pila pila = p_crear();
    NodoArbol nodo = a_establecer_raiz(arbol, te_crear(clave));
    NodoArbol nuevo;
    p_apilar(pila, te_crear_con_valor(clave, nodo));
    TipoElemento elemento = te_crear(0);
    bool izq = true;
    while (elemento) {
        printf("Ingrese nodo: ");
        bool pedido = pedirNodoN(&clave, 11);
        if (pedido) {
        if (izq) {
            nuevo = a_conectar_hi(arbol, nodo, te_crear(clave));
        } else {
            nuevo = a_conectar_hd(arbol, nodo, te_crear(clave));
        }
        izq = true;
        p_apilar(pila, te_crear_con_valor(clave, nuevo));
        nodo = nuevo;
        } else {
        elemento = p_desapilar(pila);
        izq = false;
        if (elemento) {
            nodo = elemento->valor;
        }
        }
    }
    }
}

// ==================== EJERCICIOS ====================
// funcion auxiliar recursiva que determina si dos arboles son equivalentes (en los casos bases o de no equivalentes, se retorna para cortar recursion)
void sonEquivalentes(NodoArbol nodoA, NodoArbol nodoB, bool *equivalentes) {
    // ambos nodos son nulos, son equivalentes
    if (a_es_rama_nula(nodoA) && a_es_rama_nula(nodoB)) { // caso base (fin del recorrido y siguen siendo equivalentes)
        return;
    }
    // si uno es nulo y el otro no, no son equivalentes (diferente estructura)
    if (a_es_rama_nula(nodoA) || a_es_rama_nula(nodoB)) { // caso base (no son equivalentes y se deja de hacer este subrecorrido)
        *equivalentes = false;
        return;
    }
    // si las claves de los nodos no son iguales, no son equivalentes (diferentes claves)
    if (n_recuperar(nodoA)->clave != n_recuperar(nodoB)->clave) { // caso base (no son equivalentes y se deja de hacer este subrecorrido)
        *equivalentes = false;
        return;
    }
    // caso recursivo (como no se termino de recorrer y siguen siendo equivalentes, se sigue el subrecorrido)
    sonEquivalentes(n_hijoizquierdo(nodoA), n_hijoizquierdo(nodoB), equivalentes);
    sonEquivalentes(n_hijoderecho(nodoA), n_hijoderecho(nodoB), equivalentes);
}

// funcion que retorna si dos arboles son equivalentes
bool a_ej7_equivalente(ArbolBinario A, ArbolBinario B) {
    bool equivalentes = true;
    if ((a_es_vacio(A) && !a_es_vacio(B)) || !a_es_vacio(A) && a_es_vacio(B)) {
        return false;
    } else {
        sonEquivalentes(a_raiz(A), a_raiz(B), &equivalentes);
    }
    return equivalentes;
}

int main() {
    // ingreso de datos ARBOL A
    ArbolBinario arbolA = a_crear();
    printf("=== === === Se ingresan los nodos del arbol A en PREORDEN === === ===\n");
    pedirArbol(arbolA);
    printf("=== === === === === === === === === === === === === === ===\n");
    // ingreso de datos ARBOL B
    ArbolBinario arbolB = a_crear();
    printf("=== === === Se ingresan los nodos del arbol B en PREORDEN === === ===\n");
    pedirArbol(arbolB);
    printf("=== === === === === === === === === === === === === === ===\n");

    // validacion y ejercicio
    if (a_ej7_equivalente(arbolA, arbolB)) {
        printf("Los arboles SON equivalentes.\n");
    } else {
        printf("Los arboles NO SON equivalentes.\n");
    }

    return 0;
}
