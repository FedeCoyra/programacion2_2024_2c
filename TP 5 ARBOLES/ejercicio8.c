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
// 8. Dado un árbol “n-ario” se pide
// a. Determinar la altura del mismo
void calcularAltura(NodoArbol nodo, int altura, int * alturaActual) {
  if (!a_es_rama_nula(nodo)) {
    if (altura > *alturaActual) {
      *alturaActual = altura;
    }
    calcularAltura(n_hijoizquierdo(nodo), altura + 1, alturaActual);
    calcularAltura(n_hijoderecho(nodo), altura, alturaActual);
  }
}

int c_ej8_altura(ArbolBinario A) {
    int altura = 1;
    calcularAltura(a_raiz(A), 1, &altura);
    return altura;
}

// b. Determinar el nivel de un nodo
void calcularNivel(NodoArbol nodo, int actual, int nodoA, int * nivel) {
    if (!a_es_rama_nula(nodo)) {
        if (n_recuperar(nodo)->clave == nodoA) {
            *nivel = actual;
        }
        calcularNivel(n_hijoizquierdo(nodo), actual + 1, nodoA, nivel);
        calcularNivel(n_hijoderecho(nodo), actual + 1, nodoA, nivel);
    }
}

int c_ej8_nivel(ArbolBinario A, int clave) {
    int nivel = -1;
    calcularNivel(a_raiz(A), 0, clave, &nivel);
    return nivel;
}

// c. Listar todos los nodos internos (solo las claves)
void calcularNodosInternos(NodoArbol nodo, Lista lista, bool esRaiz) {
    if (!a_es_rama_nula(nodo)) {
        if (!esRaiz && (!a_es_rama_nula(n_hijoizquierdo(nodo)) || !a_es_rama_nula(n_hijoderecho(nodo)))) {
            l_agregar(lista, n_recuperar(nodo));
        }
        calcularNodosInternos(n_hijoizquierdo(nodo), lista, false);
        calcularNodosInternos(n_hijoderecho(nodo), lista, false);
    }
}

Lista c_ej8_internos(ArbolBinario A) {
    Lista lista = l_crear();
    calcularNodosInternos(a_raiz(A), lista, true);
    return lista;
}

// d. Determinar si todas las hojas están al mismo nivel
void hojasAlMismoNivel(NodoArbol nodo, int *nivel, int nivelActual, bool *mismo) {
    if (!a_es_rama_nula(nodo)) {
        if (a_es_rama_nula(n_hijoizquierdo(nodo)) && a_es_rama_nula(n_hijoderecho(nodo))) {
            if (*nivel == -1) {
                *nivel = nivelActual;
            } else if (nivelActual != *nivel) {
                *mismo = false;
                return;
            }
        }
        hojasAlMismoNivel(n_hijoizquierdo(nodo), nivel, nivelActual + 1, mismo);
        hojasAlMismoNivel(n_hijoderecho(nodo), nivel, nivelActual + 1, mismo);
    }
}

bool c_ej8_hojasmismonivel(ArbolBinario A) {
    bool mismoNivel = true;
    int nivel = -1;
    hojasAlMismoNivel(a_raiz(A), &nivel, 1, &mismoNivel);
    return mismoNivel;
}

int main() {
    // ingreso de datos
    ArbolBinario arbol = a_crear();
    printf("=== === === Se ingresan los nodos del arbol binario transformado en PREORDEN === === ===\n");
    pedirArbol(arbol);
    printf("=== === === === === === === === === === === === === === ===\n");
    // a. Determinar la altura del mismo
    printf("\na. [ALTURA DEL ARBOL N-ARIO]\n");
    if (!a_es_vacio(arbol)) {
        printf("La altura del arbol es: %d.\n", c_ej8_altura(arbol));
    } else {
        printf("El arbol no tiene altura (ya que es vacio).\n");
    }
    // b. Determinar el nivel de un nodo
    printf("\nb. [NIVEL DE UN NODO]\n");
    printf("Ingrese la clave para utilizar: ");
    int claveBuscada;
    pedirDatos(&claveBuscada, 11);
    int nivelNodo = c_ej8_nivel(arbol, claveBuscada);
    if (nivelNodo == -1) {
        printf("La clave ingresada no esta en el arbol\n");
    } else {
        printf("El nivel en el que esta el nodo %d: %d\n", claveBuscada, nivelNodo);
    }
    // c. Listar todos los nodos internos (solo las claves)
    printf("\nc. [NODOS INTERNOS]\n");
    Lista nodosInternos = c_ej8_internos(arbol);
    if (!l_es_vacia(nodosInternos)) {
        l_mostrar(nodosInternos);
    } else {
        printf("El arbol no contiene nodos internos.\n");
    }
    // d. Determinar si todas las hojas están al mismo nivel
    printf("\nd. [HOJAS AL MIMO NIVEL?]\n");
    if (c_ej8_hojasmismonivel(arbol)) {
        printf("Las hojas estan al mismo nivel.\n");
    } else {
        printf("Las hojas no se encuentran al mismo nivel.\n");
    }

    return 0;
}
