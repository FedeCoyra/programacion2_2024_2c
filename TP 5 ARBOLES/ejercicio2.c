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

// funcion auxiliar para a. que recorre un arbol binario y mete todas las hojas en una lista
void hojas(NodoArbol nodo, Lista lista_hojas) {
    TipoElemento x;
    if (!a_es_rama_nula(nodo)) {
        x = n_recuperar(nodo);
        if (a_es_rama_nula(n_hijoderecho(nodo)) && a_es_rama_nula(n_hijoizquierdo(nodo))) {
            // x = n_recuperar(nodo);
            l_agregar(lista_hojas, x);
        }
        hojas(n_hijoizquierdo(nodo), lista_hojas); // caso recursivo izq
        hojas(n_hijoderecho(nodo), lista_hojas); // caso recursivo der
    }
}

// funcion auxiliar para funcion interiores
void interioresAux(NodoArbol nodo, Lista lista) {
    TipoElemento x;
    if (!a_es_rama_nula(nodo)) {
        if ((!a_es_rama_nula(n_hijoizquierdo(nodo))) || !a_es_rama_nula(n_hijoderecho(nodo))) {
            x = n_recuperar(nodo);
            l_agregar(lista, x);
        }
        interioresAux(n_hijoizquierdo(nodo), lista);
        interioresAux(n_hijoderecho(nodo), lista);
    }
}

// funcion auxiliar para b. que busca y agrega los elementos de los nodos interiores de un arbol binario a una lista
void interiores(ArbolBinario arbol, Lista lista) {
    NodoArbol raiz = a_raiz(arbol);
    interioresAux(n_hijoizquierdo(raiz), lista);
    interioresAux(n_hijoderecho(raiz), lista);
}

// esta funcion busca en un arbol binario todas las ocurrencias de un valor clave especifico y las agrega a una lista
void lista_ocurrencias(NodoArbol nodo, Lista l_ocurrencias, int clave) {
    TipoElemento x;
    if (!a_es_rama_nula(nodo)){
        x = n_recuperar(nodo);
        if (x->clave == clave){
            l_agregar(l_ocurrencias,x);
        }
        lista_ocurrencias(n_hijoizquierdo(nodo), l_ocurrencias, clave);
        lista_ocurrencias(n_hijoderecho(nodo), l_ocurrencias, clave);
    }
}

// se pide un entero al usuario y se valida que sea correcto.
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
// a. Retornar una lista con todos los nodos terminales u hojas
Lista a_ej2_hojas(ArbolBinario A) {
    Lista nodosHoja = l_crear();
    hojas(a_raiz(A), nodosHoja);
    return nodosHoja;
}

// b. Retornar en una estructura todos los nodos interiores
Lista a_ej2_interiores(ArbolBinario A) {
    Lista nodosInteriores = l_crear();
    interiores(A, nodosInteriores);
    return nodosInteriores;
}

// c. Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la posición de cada ocurrencia (puntero al nodo)
Lista a_ej2_buscarclave(ArbolBinario A, int clave) {
    Lista ocurrencias = l_crear();
    lista_ocurrencias(a_raiz(A), ocurrencias, clave);
    return ocurrencias;
}

int main() {
    // ingreso de datos
    ArbolBinario arbol = a_crear();
    printf("=== === === Se ingresan los nodos del arbol en PREORDEN === === ===\n");
    pedirArbol(arbol);
    printf("=== === === === === === === === === === === === === === ===\n");

    // si el arbol es vacio, no se hacen los procedimientos
    if (a_es_vacio(arbol)) {
        printf("Arbol vacio.\n");
    } else {
        mostrar_arbol_pre_ord(a_raiz(arbol));
        // a. Retornar una lista con todos los nodos terminales u hojas
        printf("\na. [NODOS HOJA]\n");
        Lista listaHojas = a_ej2_hojas(arbol);
        if (!l_es_vacia(listaHojas)) {
            l_mostrar(listaHojas);
        } else {
            printf("No hay nodos hojas.\n");
        }
        free(listaHojas);
        // ---

        //  b.	Retornar en una estructura todos los nodos interiores
        printf("\nb. [NODOS INTERIORES]\n");
        Lista listaIntermedios = a_ej2_interiores(arbol);
        if (!l_es_vacia(listaIntermedios)) {
            l_mostrar(listaIntermedios);
        } else {
            printf("No hay nodos interiores.\n");
        }
        free(listaIntermedios);
        // ---

        //  c.	Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la posición de cada ocurrencia
        printf("\nc. [OCURRENCIAS DE LA CLAVE]\n");
        printf("Ingrese una clave para enlistar las ocurrencias de esta en el arbol:");
        int claveDeOcurrencia;
        pedirDatos(&claveDeOcurrencia, 11);
        Lista ocurrencias = a_ej2_buscarclave(arbol, claveDeOcurrencia);
        if (!l_es_vacia(ocurrencias)) {
           l_mostrar(ocurrencias);
        } else {
            printf("No hay ocurrencias.\n");
        }
        free(ocurrencias);
        // ---
    }
    free(arbol);
    return 0;
}
