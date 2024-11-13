#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "tabla_hash.h"
#include "arbol-avl.h"
#include "listas.h"
#include "tipo_elemento.h"
#include "nodo.h"

#define TAMANIO_MAXIMO_TH 2000
#define N_PRIMO 1999

int funcionHashModulo (int a) {
  return (a % N_PRIMO);
}

void cargarAleatorio(ArbolAVL arbol, TablaHash tabla, int rango, int cantidad) {
  srand(time(NULL));
  int i = 0;
  TipoElemento valor;
  int numeroRandom;
  while (i < cantidad){
    numeroRandom = (rand() % rango) + 1;
    if (!avl_buscar(arbol, numeroRandom)) {
      valor = te_crear(numeroRandom);
      avl_insertar(arbol, valor);
      th_insertar(tabla, valor);
      i++;
    }
  }
}

void busquedaTest (int cantIteraciones, int rango, int cantidad) {
  int i;
  clock_t start_avl, end_avl, start_hash, end_hash;
  double tiempo_avl = 0.0, tiempo_hash = 0.0;

  ArbolAVL arbol = avl_crear();
  TablaHash tabla = th_crear(TAMANIO_MAXIMO_TH, &funcionHashModulo);
  cargarAleatorio(arbol, tabla, rango, cantidad);
  int numeroBuscar;

  srand(time(NULL));

  for (int j = 0; j < cantIteraciones; j++){
    start_hash = clock();
    numeroBuscar = rand() % rango + 1;
    th_recuperar(tabla,numeroBuscar);
    end_hash = clock();
    tiempo_hash += (double)(end_hash - start_hash) / CLOCKS_PER_SEC;
  }

  for (int j = 0; j < cantIteraciones; j++){
    start_avl = clock();
    numeroBuscar = rand() % rango + 1;
    avl_buscar(arbol,numeroBuscar);
    end_avl = clock();
    tiempo_avl += (double)(end_avl - start_avl) / CLOCKS_PER_SEC;
  }
  free(arbol);
  free(tabla);
  printf("Tiempo de respuesta del arbol (En segundos): %.32lf \n", tiempo_avl);
  printf("Tiempo de respuesta del hash (En segundos): %.32lf \n", tiempo_hash);
}

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
    do{
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

int main () {
  int cantIte, rango, cantElementos;
  do {
    printf("Ingrese la cantidad de elementos que tendran ambas estructuras (entre 1 y 2000): ");
    pedirDatos(&cantElementos, 11);
    if (cantElementos < 1 || cantElementos > 2000)
      printf("Valor fuera de rango.\n");
  } while (cantElementos < 1 || cantElementos > 2000);

  do{
    printf("\nIngrese rango de las claves (va desde 1 hasta el valor que ingrese): ");
    pedirDatos(&rango, 11);
    if (rango < cantElementos)
      printf("El rango ingresado debe ser mayor o igual a la cantidad que usted ingreso (%d).\n", cantElementos);
  } while (rango < cantElementos);

  do{
    printf("\nIngrese la cantidad de busquedas a realizar (Se recomiendan valores altos para obtener resultados contundentes entre 1 y 9.999.999): ");
    pedirDatos(&cantIte, 11);
    if (cantIte < 1 || cantIte > 9999999)
      printf("Entrada invalida.\n");
  } while (cantIte < 1 || cantIte > 9999999);

  busquedaTest(cantIte, rango, cantElementos);

  printf("\nSe concluye que la tabla Hash es mas eficiente que Arbol AVL cuando se utiliza la implementacion de listas enlazadas\n");
  printf("Sin embargo, al utilizar la implementacion de zona overflow, el AVL realiza las busquedas en menor tiempo que Hash\n");

  return 0;
}
