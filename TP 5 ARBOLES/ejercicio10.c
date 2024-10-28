#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "arbol-binario.h"
#include "tipo_elemento.h"
#include "nodo.h"
#include "listas.h"
#include "colas.h"
#include "pilas.h"
#include "arbol-avl.h"
#include "arbol-binario-busqueda.h"

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

void cargarAleatorio(ArbolBinarioBusqueda ABB, ArbolAVL AVL, int rango, int cantidad) {
    int i = 0;
    TipoElemento valor;
    while (i < cantidad){
        int numeroRandom = (rand() % rango) + 1;
        if (!avl_buscar(AVL, numeroRandom)) {
            valor = te_crear(numeroRandom);
            abb_insertar(ABB, valor);
            avl_insertar(AVL, valor);
            i++;
        }
    }
}

void calcularAltura(NodoArbol nodo, int *alt, int contador) {
    if (a_es_rama_nula(nodo)) {
        if (contador > *alt) {
            *alt = contador;
        }
    }
    else {
        calcularAltura(n_hijoizquierdo(nodo), alt, contador++);
        calcularAltura(n_hijoderecho(nodo), alt, contador++);
    }
}

int alturaBB (ArbolBinarioBusqueda arbol) {
  int alt = 0;
  calcularAltura(abb_raiz(arbol), &alt, -1);
  return alt;
}

int alturaAVL (ArbolAVL arbol) {
  int alt = 0;
  calcularAltura(avl_raiz(arbol), &alt, -1);
  return alt;
}

void generarArboles (int cantArboles, int rango, int cantidad) {
    int i;
    srand(time(NULL));
    int sumaBB = 0;
    int sumaAVL = 0;
    int menorBB;
    int menorAVL;
    int mayorBB = 0;
    int mayorAVL = 0;
    for (i = 0; i < cantArboles; i++) {
        ArbolBinarioBusqueda arbolbb = abb_crear();
        ArbolAVL arbolavl = avl_crear();
        cargarAleatorio(arbolbb, arbolavl, rango, cantidad);
        int altBB = alturaBB(arbolbb);
        int altAVL = alturaAVL(arbolavl);
        printf("Arbol numero %d\n", i + 1);
        printf("Altura del arbol BB: %d\n", altBB);
        printf("Altura del arbol AVL: %d\n", altAVL);
        if (i == 0) {
            menorBB = altBB;
            menorAVL = altAVL;
        }
        if (menorBB > altBB) {
            menorBB = altBB;
        }
        if (menorAVL > altAVL) {
            menorAVL = altAVL;
        }
        if (mayorBB < altBB) {
            mayorBB = altBB;
        }
        if (mayorAVL < altAVL) {
            mayorAVL = altAVL;
        }
        sumaBB += altBB;
        sumaAVL += altAVL;
        free(arbolbb);
        free(arbolavl);
    }
    printf("\n");
    printf("La mayor altura de los binarios de busqueda es: %d\n", mayorBB);
    printf("La menor altura de los binarios de busqueda es: %d\n", menorBB);
    printf("\n");
    printf("La mayor altura de los AVL es: %d\n", mayorAVL);
    printf("La menor altura de los AVL es: %d\n", menorAVL);
    printf("\n");
    printf("El promedio de binarios de busqueda es: %.4f\n", (float)sumaBB / cantArboles);
    printf("El promedio de AVL es: %.4f\n", (float)sumaAVL / cantArboles);
}

int main() {
    int cantElementos;
    int cantArboles;
    int rango;
    do {
        printf("Ingrese cantidad de elementos en los arboles (entre 0 y %d): ", 2000);
        pedirDatos(&cantElementos, 11);
        if (cantElementos > 2000 || cantElementos < 0) {
            printf("La cantidad ingresada no es valida, ingrese otra por favor.\n");
        }
    } while (cantElementos > 2000 || cantElementos < 0);

    do {
        printf("Ingrese la cantidad de arboles a generar (entre 1 y 200): ");
        pedirDatos(&cantArboles, 11);
        if (cantArboles > 200 || cantArboles <= 0) {
            printf("La cantidad ingresada no es valida, ingrese otra por favor.\n");
        }
    } while (cantArboles > 200 || cantArboles <= 0);

    do {
        printf("Ingrese el rango de los numeros aleatorios: ");
        pedirDatos(&rango, 11);
        if (rango < cantElementos) {
            printf("El rango de datos tiene que ser mayores a los arboles, para que no se repitan.\n");
        }
    } while (rango < cantElementos);

    generarArboles(cantArboles, rango, cantElementos);
    printf("\n");
    printf("Se puede concluir que la estructura de los arboles AVL en comparacion a los ABB tiene la capacidad de reducir la altura del arbol, por lo que suma eficiencia a la hora de insertar, eliminar o buscar algun nodo/clave. Tambien, el AVL evita que el arbol se degenere en una lssta enlazada, evitando, de vuelta, problemas de eficiencia.\n");

    return 0;
}
