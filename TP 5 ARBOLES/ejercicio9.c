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
#include "colas.h"
#include "pilas.h"
#include "arbol-avl.h"

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

void pedirDatos(int *nro, int tamanio) {
    bool conversionCorrecta = true;
    do {
        char * bufferNro = malloc(sizeof(char) * tamanio);
        fgets(bufferNro, tamanio, stdin);
        conversionCorrecta = conversionEntero(bufferNro, nro, tamanio);
        if (!conversionCorrecta){
            printf("El numero es invalido, revisa los requerimientos\n");
            printf("Ingrese otro numero: ");
            fflush(stdin);
        }
    } while (!conversionCorrecta);
}

// ==================== EJERCICIOS ====================
ArbolAVL construirAVL(NodoArbol actual, ArbolAVL avl) {
    TipoElemento temp;
    if (!a_es_rama_nula(actual)) {
        temp = n_recuperar(actual);
        avl_insertar(avl, temp);
        construirAVL(n_hijoizquierdo(actual), avl);
        construirAVL(n_hijoderecho(actual), avl);
    }
}

ArbolAVL a_ej9_construiravl(ArbolBinario A) {
    ArbolAVL arbolAVL = avl_crear();
    construirAVL(a_raiz(A), arbolAVL);
    return arbolAVL;
}

void calcularAltura(NodoArbol actual, int c, int *altura) {
    if (!a_es_rama_nula(actual)) {
        if (c > *altura)
            *altura = c;

        // Recorre en pre-orden y aumento la altura cada vez que bajo.
        calcularAltura(n_hijoizquierdo(actual), c + 1, altura);
        calcularAltura(n_hijoderecho(actual), c + 1, altura);
    }
}

int a_ej9_diferenciaalturas(ArbolBinario A, ArbolAVL AVL, int *alturaB, int *alturaAVL) {
    *alturaB = 0;
    *alturaAVL = 0;

    // Calcula la altura del árbol binario
    calcularAltura(a_raiz(A), 0, alturaB);

    // Calcula la altura del árbol AVL
    calcularAltura(avl_raiz(AVL), 0, alturaAVL);

    // Retorna la diferencia entre las dos alturas
    return *alturaB - *alturaAVL;
}

int main() {
    // ingreso de datos - ARBOL BINARIO
    ArbolBinario arbol = a_crear();
    printf("=== === === Se ingresan los nodos del arbol binario transformado en PREORDEN === === ===\n");
    pedirArbol(arbol);
    printf("=== === === === === === === === === === === === === === ===\n");
    // creo AVL a partir del AB
    ArbolAVL AVL = a_ej9_construiravl(arbol);

    // Variables para almacenar las alturas
    int alturaB, alturaAVL;
    int diferencia = a_ej9_diferenciaalturas(arbol, AVL, &alturaB, &alturaAVL);

    // Mostrar las alturas y la diferencia
    printf("La altura del arbol binario es: %d.\n", alturaB);
    printf("La altura del arbol AVL es: %d.\n", alturaAVL);
    printf("La diferencia de alturas entre el arbol binario y el AVL es: %d.\n", diferencia);

    return 0;
}
