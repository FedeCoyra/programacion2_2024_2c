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

// a. Dado un árbol n-ario, devolver en forma de lista el resultado del recorrido en anchura del árbol.
void recorrerHermanos(NodoArbol nodo, Lista lista, Cola colaAux) {
    if (!a_es_rama_nula(nodo)) {
        l_agregar(lista, n_recuperar(nodo));
        if (!a_es_rama_nula(n_hijoizquierdo(nodo))) { // agrega a la cola los HI de cada HD
            c_encolar(colaAux, te_crear_con_valor(n_recuperar(n_hijoizquierdo(nodo))->clave, n_hijoizquierdo(nodo)));
        }
        recorrerHermanos(n_hijoderecho(nodo), lista, colaAux);
    }
}

void recorrerAnchura(NodoArbol nodo, Lista lista, Cola colaAux) {
    // si el nodo es nulo, no queda otra que recorrer la cola (con los HI)
    if (a_es_rama_nula(nodo)) {
        if (!c_es_vacia(colaAux)) {
            nodo = (NodoArbol)c_desencolar(colaAux)->valor; // saco el 1er HI
        } else { // si ya no quedan HI, es porque en el n-ario no hay mas niveles
            return;
        }
    }

    if (!a_es_rama_nula(nodo)) {
        l_agregar(lista, n_recuperar(nodo));
        // si en el nodo hay un HI se guarda
        if (!a_es_rama_nula(n_hijoizquierdo(nodo))) {
            c_encolar(colaAux, te_crear_con_valor(n_recuperar(n_hijoizquierdo(nodo))->clave, n_hijoizquierdo(nodo)));
        }
        // luego, recorre todos los hermanos y en cada hermano almacena si hay un HI
        if (!a_es_rama_nula(n_hijoderecho(nodo))) {
            recorrerHermanos(n_hijoderecho(nodo), lista, colaAux); // se agregan los hermanos del nodo
        }
        // haciendo todo esto se toman todos los HI que pertenecen al siguiente nivel
        // y se agregan directamente los HD (que son hermanos y deben agregarse juntos)

        // llama recursivamente con NULL para procesar el siguiente nodo en la cola
        // es NULL ya que eso va a provocar que el programa busque en la cola por los HI
        // que le permitiran saltar al siguiente nivel
        recorrerAnchura(NULL, lista, colaAux);
    }
}

Lista a_ej4_anchura(ArbolBinario A) {
    Lista lista = l_crear();
    Cola cola = c_crear();
    l_agregar(lista, n_recuperar(a_raiz(A)));
    recorrerAnchura(n_hijoizquierdo(a_raiz(A)), lista, cola);
    return lista;
}

// b. Escribir una función que, dado un árbol n-ario, devuelva el número (cantidad) de hojas de dicho árbol.
void cantidadHojas(NodoArbol nodo, int *cantidad) {
    if (a_es_rama_nula(nodo)) { // caso base
        return;
    } else { // caso recursivo
        if (a_es_rama_nula(n_hijoizquierdo(nodo))) {
            *cantidad = *cantidad + 1;
            cantidadHojas(n_hijoderecho(nodo), cantidad);
        } else {
            cantidadHojas(n_hijoizquierdo(nodo), cantidad);
            cantidadHojas(n_hijoderecho(nodo), cantidad);
        }
    }
}

int a_ej4_q_hojas(ArbolBinario A) {
    int cantidad = 0;
    cantidadHojas(a_raiz(A), &cantidad);
    return cantidad;
}

// c. Escribir una función booleana que dados dos árboles generales determine si tienen la misma estructura, sin importar los datos del mismo (árbol similar).
void sonSimilares(NodoArbol nodoA, NodoArbol nodoB, bool *similares) {
    // ambos nodos son nulos, son similares
    if (a_es_rama_nula(nodoA) && a_es_rama_nula(nodoB)) { // caso base (fin del recorrido y siguen siendo similares)
        return;
    }
    // si uno es nulo y el otro no, no son similares (diferente estructura)
    if (a_es_rama_nula(nodoA) || a_es_rama_nula(nodoB)) { // caso base (no son equivalentes y se deja de hacer este subrecorrido)
        *similares = false;
        return;
    }
    // caso recursivo (como no se termino de recorrer y siguen siendo similares, se sigue el subrecorrido)
    sonSimilares(n_hijoizquierdo(nodoA), n_hijoizquierdo(nodoB), similares);
    sonSimilares(n_hijoderecho(nodoA), n_hijoderecho(nodoB), similares);
}

bool a_ej4_similares(ArbolBinario A, ArbolBinario B) {
    bool similares = true;
    if ((a_es_vacio(A) && !a_es_vacio(B)) || !a_es_vacio(A) && a_es_vacio(B)) {
        return false;
    } else {
        sonSimilares(a_raiz(A), a_raiz(B), &similares);
    }
    return similares;
}

// d. Retornar el padre de un nodo del árbol (tipo_elemento).
void padreRecursivo(NodoArbol nodo, NodoArbol padreActual, int clave, NodoArbol *padre) {
    if (!a_es_rama_nula(nodo)) {
        if (clave == n_recuperar(nodo)->clave) {
            *padre = padreActual;
        } else {
            padreRecursivo(n_hijoizquierdo(nodo), nodo, clave, padre);
            padreRecursivo(n_hijoderecho(nodo), padreActual, clave, padre);
        }
    }
}

NodoArbol padreAux(ArbolBinario arbol, int clave) {
  NodoArbol padre = NULL;
  padreRecursivo(n_hijoizquierdo(a_raiz(arbol)), a_raiz(arbol), clave, &padre);
  return padre;
}

TipoElemento a_ej4_padre(ArbolBinario A, int clave) {
    NodoArbol padreDelNodo = padreAux(A, clave);
    if (!a_es_rama_nula(padreDelNodo)) {
        return n_recuperar(padreDelNodo);
    } else {
        printf("No se encontro el padre (se retornara un TE con la clave -999).\n");
        return te_crear(-999);
    }
}

// e. Retornar los hermanos de un nodo del árbol (lista de hermanos).
void listarAnchura(NodoArbol nodo, Lista lista, int hijo) {
    if (!a_es_rama_nula(nodo)) {
        if (n_recuperar(nodo)->clave != hijo) {
            l_agregar(lista, n_recuperar(nodo));
        }
        listarAnchura(n_hijoderecho(nodo), lista, hijo);
    }
}

Lista a_ej4_hermanos(ArbolBinario A, int clave) {
    NodoArbol nodoPadre = padreAux(A, clave);
    Lista lista = l_crear();
    if (!a_es_rama_nula(nodoPadre)) {
        listarAnchura(n_hijoizquierdo(nodoPadre), lista, clave);
    }
    return lista;
}

int main() {
    // ingreso de datos ARBOL A
    ArbolBinario arbolA = a_crear();
    printf("=== === === Se ingresan los nodos del arbol binario transformado A en PREORDEN === === ===\n");
    pedirArbol(arbolA);
    printf("=== === === === === === === === === === === === === === ===\n");
    // a. Recorrido de anchura de binario transformado (Knuth)
    printf("\na. Recorrido en anchura de binario transformado (Knuth)\n");
    Lista listaAnchura = a_ej4_anchura(arbolA);
    l_mostrar(listaAnchura);
    // b. Cantidad de hojas del n-ario
    printf("\nb. Cantidad de hojas del n-ario\n");
    printf("%d hojas", a_ej4_q_hojas(arbolA));
    // c. Determinar si dos arboles n-arios son similares
    printf("\nc. Arboles similares\n");
    ArbolBinario arbolB = a_crear();
    printf("\n=== === === Se ingresan los nodos del arbol transformado B en PREORDEN === === ===\n");
    pedirArbol(arbolB);
    printf("=== === === === === === === === === === === === === === ===\n");
    if (a_ej4_similares(arbolA, arbolB)) {
        printf("Los arboles son similares.\n");
    } else {
        printf("Los arboles NO son similares.\n");
    }
    // d. Retornar el padre de un nodo del árbol (tipo_elemento)
    printf("\nd. Padre de un nodo del arbol\n");
    printf("Ingrese la clave para utilizar: ");
    int claveBuscada;
    pedirDatos(&claveBuscada, 11);
    if (!a_es_vacio(arbolA)) {
        if (n_recuperar(a_raiz(arbolA))->clave == claveBuscada) {
            printf("La clave buscada es la raiz (no tiene padre).\n");
        } else {
            printf("El padre de la clave pedida es %d.\n", a_ej4_padre(arbolA, claveBuscada)->clave);
        }
    } else {
        printf("El arbol es vacio.\n");
    }
    // e. Retornar los hermanos de un nodo del árbol (lista de hermanos).
    printf("\ne. Retornar los hermanos de un nodo\n");
    printf("Ingrese la clave para utilizar: ");
    claveBuscada = 0;
    pedirDatos(&claveBuscada, 11);
    if (!a_es_vacio(arbolA)) {
        Lista listaHermanos = l_crear();
        listaHermanos = a_ej4_hermanos(arbolA, claveBuscada);
        if (!l_es_vacia(listaHermanos)) {
            printf("Hermanos del nodo:\n");
            l_mostrar(listaHermanos);
        } else {
            printf("No tiene hermanos o no existe en el arbol.\n");
        }
    } else {
        printf("El arbol es vacio.\n");
    }
    return 0;
}
