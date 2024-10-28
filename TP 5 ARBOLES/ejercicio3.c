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
    while(isspace(string[i]))
        i++;
    if (len == i) return false;

    char * buffer = malloc(sizeof(char)*len);
    int indiceEntero = 0;
    if (string[i] == '-'){
        buffer[indiceEntero] = '-';
        indiceEntero++;
        i++;

        if (!isdigit(string[i])) return false;
    }

    while (i < len && !isspace(string[i])){
        if (!isdigit(string[i])) return false;
        buffer[indiceEntero] = string[i];
        indiceEntero++;
        i++;
    }
    buffer[indiceEntero] = '\0';
    while (isspace(string[i]))
        i++;

    if (string[i] != '\0') return false;

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

// funciones que verifican si una clave ya existe en el arbol binario
bool existeClaveAux(NodoArbol nodo, int claveBuscada) {
    if (a_es_rama_nula(nodo)) {
        return false;
    } else {
        TipoElemento X = n_recuperar(nodo);
        if (X->clave == claveBuscada) {
            return true;
        } else {
            return existeClaveAux(n_hijoizquierdo(nodo), claveBuscada) || existeClaveAux(n_hijoderecho(nodo), claveBuscada);
        }
    }
}

bool existeClave(ArbolBinario arbol, int clave) {
    return existeClaveAux(a_raiz(arbol), clave);
}

// funcion que pide y rellena con datos un arbol binario
void pedirArbolSinRepetidos (ArbolBinario arbol) {
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
                while (existeClave(arbol, clave)) {
                    printf("Esa clave ya existe dentro del arbol. Ingrese otra clave: ");
                    pedido = pedirNodoN(&clave, 11);
                }
            }
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

// funcion que pide un entero al usuario y se valida que sea correcto.
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
// a. Indicar el nombre del nodo padre (clave)
int encontrarPadre(NodoArbol nodo, int clave) {
    // verificar si el nodo actual es nulo
    if (nodo == NULL) return -1;

    // recuperar el elemento actual y los elementos de los hijos
    TipoElemento elementoActual = n_recuperar(nodo);
    TipoElemento elementoSigIzq = n_recuperar(n_hijoizquierdo(nodo));
    TipoElemento elementoSigDer = n_recuperar(n_hijoderecho(nodo));

    // verificar si los hijos no son nulos y si tienen la clave buscada
    if (elementoSigIzq != NULL && elementoSigIzq->clave == clave) return elementoActual->clave;
    if (elementoSigDer != NULL && elementoSigDer->clave == clave) return elementoActual->clave;

    // llamadas recursivas para los hijos
    int padreIzq = encontrarPadre(n_hijoizquierdo(nodo), clave);
    if (padreIzq != -1) return padreIzq;
    int padreDer = encontrarPadre(n_hijoderecho(nodo), clave);
    if (padreDer != -1) return padreDer;

    return -1;
}

int a_ej3_clavepadre(ArbolBinario A, int clavehijo) {
    NodoArbol raiz = a_raiz(A);
    TipoElemento elementoRaiz = n_recuperar(raiz);
    if (elementoRaiz->clave == clavehijo) {
        printf("La raiz no tiene padre (se retornara el -1 por default).\n");
        return -1;
    } else {
        return encontrarPadre(raiz, clavehijo);
    }
}

// b. Listar los hijos (solo las clave/s)
void encontrarHijos(NodoArbol nodo, int clave, Lista claves) {
    if (!a_es_rama_nula(nodo)) {
        TipoElemento elementoActual, elementoSigIzq, elementoSigDer;
        elementoActual = n_recuperar(nodo);
        elementoSigIzq = n_recuperar(n_hijoizquierdo(nodo));
        elementoSigDer = n_recuperar(n_hijoderecho(nodo));
        if (elementoActual->clave == clave) {
            if (elementoSigIzq != NULL) l_agregar(claves, elementoSigIzq);
            if (elementoSigDer != NULL) l_agregar(claves, elementoSigDer);
        } else {
            encontrarHijos(n_hijoizquierdo(nodo), clave, claves);
            encontrarHijos(n_hijoderecho(nodo), clave, claves);
        }
    }
}

Lista a_ej3_hijos(ArbolBinario A, int clavepadre) {
    Lista clavesHijos = l_crear();
    encontrarHijos(a_raiz(A), clavepadre, clavesHijos);
    return clavesHijos;
}

// c. Listar el hermano (solo la clave)
int encontrarHermano(NodoArbol nodo, int clave, bool *encontrado) {
    if (a_es_rama_nula(nodo)) {
        return -1;
    }
    TipoElemento elementoSigIzq = n_recuperar(n_hijoizquierdo(nodo));
    TipoElemento elementoSigDer = n_recuperar(n_hijoderecho(nodo));

    // verificar si los elementos no son nulos antes de acceder a sus claves
    if (!a_es_rama_nula(n_hijoderecho(nodo)) && elementoSigDer->clave == clave) {
        if (!a_es_rama_nula(n_hijoizquierdo(nodo))) {
            *encontrado = true;
            return elementoSigIzq->clave;
        } else {
            return -1;
        }
    } else if (!a_es_rama_nula(n_hijoizquierdo(nodo)) && elementoSigIzq->clave == clave) {
        if (!a_es_rama_nula(n_hijoderecho(nodo))) {
            *encontrado = true;
            return elementoSigDer->clave;
        } else {
            return -1;
        }
    } else {
        int izquierdo = encontrarHermano(n_hijoizquierdo(nodo), clave, encontrado);
        if (izquierdo != -1) {
            *encontrado = true;
            return izquierdo;
        };
        int derecho = encontrarHermano(n_hijoderecho(nodo), clave, encontrado);
        if (derecho != -1) {
            *encontrado = true;
            return derecho;
        }
    }
    return -1;
}

int a_ej3_hermano(ArbolBinario A, int clave) {
    bool encontrado = false;
    int hermano = encontrarHermano(a_raiz(A), clave, &encontrado);
    if (encontrado) {
        return hermano;
    } else {
        printf("No tiene hermanos (se retornara un -1 por default).\n");
        return -1;
    }
}

// d. Calcular el nivel en el que se encuentra
int calcularNivel(NodoArbol nodo, int clave, int contador) {
    int nivelEncontrado = -1; // inicialmente asumo que la clave no se encontro

    if (!a_es_rama_nula(nodo)) {
        TipoElemento elementoActual = n_recuperar(nodo);
        if (elementoActual->clave == clave) {
            return contador;
        } else {
            // incremento el contador para el siguiente nivel
            ++contador;
            // llamadas recursivas y actualizacion del nivel encontrado
            int nivelIzq = calcularNivel(n_hijoizquierdo(nodo), clave, contador);
            int nivelDer = calcularNivel(n_hijoderecho(nodo), clave, contador);
            if (nivelIzq != -1) nivelEncontrado = nivelIzq; // si la clave se encuentra en el subarbol izquierdo
            if (nivelDer != -1) nivelEncontrado = nivelDer; // si la clave se encuentra en el subarbol derecho
        }
    }
    return nivelEncontrado; // devuelvo el nivel encontrado (o -1 si no se encontro la clave)
}

int a_ej3_nivel(ArbolBinario A, int clave) {
    if (a_es_rama_nula(a_raiz(A))) {
        printf("Arbol vacio (se retorna -1).\n");
        return -1;
    } else {
        return calcularNivel(a_raiz(A), clave, 0);
    }
}

// e. Calcular la altura de su rama (Altura del Subárbol)
int calcularAltura(NodoArbol nodo, int clave, bool pasoClave) {
    if (a_es_rama_nula(nodo)) {
        return 0; // altura de un arbol nulo es 0
    }

    TipoElemento elementoActual = n_recuperar(nodo);
    if (elementoActual->clave == clave) {
        pasoClave = true;
    }

    if (pasoClave) {
        int alturaIzq = calcularAltura(n_hijoizquierdo(nodo), clave, pasoClave);
        int alturaDer = calcularAltura(n_hijoderecho(nodo), clave, pasoClave);
        return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
    } else {
        int alturaIzq = calcularAltura(n_hijoizquierdo(nodo), clave, pasoClave);
        int alturaDer = calcularAltura(n_hijoderecho(nodo), clave, pasoClave);
        return (alturaIzq > alturaDer ? alturaIzq : alturaDer);
    }
}

int a_ej3_alturarama(ArbolBinario A, int clave) {
    return calcularAltura(a_raiz(A), clave, false);
}

// f. Listar todos los nodos que están en el mismo nivel (solo la clave)
void mismoNivel(ArbolBinario arbol, NodoArbol nodo, int nivel, Lista lista) {
    if (a_es_rama_nula(nodo)) { // caso base (se recorrio todo)
        return;
    } else {
        TipoElemento elementoActual = n_recuperar(nodo);
        int nivelActual = a_ej3_nivel(arbol, elementoActual->clave);
        if (nivel == nivelActual) {
            l_agregar(lista, elementoActual);
        }
        mismoNivel(arbol, n_hijoizquierdo(nodo), nivel, lista);
        mismoNivel(arbol, n_hijoderecho(nodo), nivel, lista);
    }
}

Lista a_ej3_clavesmismonivel(ArbolBinario A, int nivel) {
    Lista l_mismoNivel = l_crear();
    mismoNivel(A, a_raiz(A), nivel, l_mismoNivel);
    return l_mismoNivel;
}

int main() {
    // ingreso de datos
    ArbolBinario arbol = a_crear();
    printf("=== === === Se ingresan los nodos del arbol en PREORDEN === === ===\n");
    pedirArbolSinRepetidos(arbol);
    printf("=== === === === === === === === === === === === === === ===\n");

    if (a_es_vacio(arbol)) {
        printf("El arbol es vacio.\n");
    } else {
        mostrar_arbol_pre_ord(a_raiz(arbol));
        printf("\nIngrese la clave para utilizar: ");
        int claveBuscada;
        pedirDatos(&claveBuscada, 11);
        // a. Indicar el nombre del nodo padre (clave)
        printf("\na. [CLAVE DEL NODO PADRE]\n");
        printf("La clave es %d\n", (a_ej3_clavepadre(arbol, claveBuscada)));
        // b. Listar los hijos (solo las clave/s)
        printf("\nb. [TODOS LOS HIJOS DE LA CLAVE]\n");
        Lista hijos = a_ej3_hijos(arbol, claveBuscada);
        if (!l_es_vacia(hijos)) {
            l_mostrar(hijos);
        } else {
            printf("La clave no existe o la clave existe pero no tiene hijos.\n");
        }
        // c. Listar el hermano (solo la clave)
        printf("\nc. [CLAVE DEL HERMANO]\n");
        printf("La clave del hermano es %d\n", a_ej3_hermano(arbol, claveBuscada));
        // d. Calcular el nivel en el que se encuentra
        printf("\nd. [NIVEL DE LA CLAVE DADA]\n");
        int nivel = a_ej3_nivel(arbol, claveBuscada);
        if (nivel == -1) {
            printf("La clave buscada no esta en el arbol.\n");
        } else {
           printf("El nivel en donde se encuentra es %d\n", nivel);
        }
        // e. Calcular la altura de su rama (Altura del Subárbol)
        printf("\ne. [ALTURA DEL SUBARBOL]\n");
        printf("La altura es %d (0 por default si la clave no existe)\n", a_ej3_alturarama(arbol, claveBuscada));
        // f. Listar todos los nodos que están en el mismo nivel (solo la clave)
        printf("\nf. [CLAVES DE LOS NODOS AL MISMO NIVEL]\n");
        printf("\nIngrese el nivel donde buscar los nodos: ");
        claveBuscada = 0;
        pedirDatos(&claveBuscada, 11);
        Lista clavesNivel = a_ej3_clavesmismonivel(arbol, claveBuscada);
        if (l_es_vacia(clavesNivel)) {
            printf("Ese nivel no existe o las claves son nulas.\n");
        } else {
            l_mostrar(clavesNivel);
        }
    }
    return 0;
}
