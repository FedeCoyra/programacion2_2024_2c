#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "colas.h"
#include "pilas.h"
#include "listas.h"

// ESTE CODIGO NECESITA IMPLEMENTAR PILAS LISTAS Y COLAS!

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
            printf("Entrada invalida. Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion que pide una cola y la copia sin alterar su version original
Cola copiar_cola(Cola colaOriginal) {
    Cola colaAuxiliar = c_crear();
    Cola colaCopia = c_crear();
    while (!c_es_vacia(colaOriginal)) {
        TipoElemento elemento = c_desencolar(colaOriginal);
        c_encolar(colaAuxiliar, elemento);
    }
    while (!c_es_vacia(colaAuxiliar)) {
        TipoElemento elemento = c_desencolar(colaAuxiliar);
        c_encolar(colaCopia, elemento);
        c_encolar(colaOriginal, elemento);
    }
    return colaCopia;
}

// funcion que pide una pila y la copia sin alterar su version original
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

// funcion que pide una lista y una clave y verifica si esta en la lista
bool estaEnLista(Lista L, int dato) {
    Iterador iter = iterador(L);
    TipoElemento X;
    bool resultado = false;
    while (hay_siguiente(iter) && (resultado == false)){
        X = siguiente(iter);
        if (X->clave == dato){
            resultado = true;
        }
    }
    return resultado;
}

// funcion que retorna si un rango es valido o no (usado para pedir rango de los random)
bool rangoValido(int randomMax, int randomMin, int tamano) {
    if ((randomMax - randomMin + 1) >= tamano) {
        return true;
    } else {
        return false;
    }
}

// funcion para llenar una cola al azar usando rango de randoms
Cola llenar_cola_al_azar() {
    Cola cola = c_crear();
    Lista listaAux = l_crear();
    printf("[INGRESO - COLA]\n");
    printf("Ingrese la longitud de la cola (entre 0 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la cola, solo se cargaran hasta que se llene la misma.\n");
    int tamano = leer_entero();
    while (tamano < 0 || tamano > 100000) {
        printf("Entrada invalida. Fuera del rango disponible para la cola. Reingrese el tamanio. ");
        tamano = leer_entero();
    }
    if (tamano == 0) {
        printf("COLA VACIA!\n");
        return cola;
    }
    int randomMin = 0;
    int randomMax = 0;
    printf("[INGRESO - RANGO DE VALORES DEL RANDOM PARA CARGAR COLA]\n");
    printf("Ingrese el valor minimo de los valores random (entre -100.000 y 100.000): ");
    randomMin = leer_entero();
    printf("\n");
    printf("Ingrese el valor maximo de los valores random (entre -100.000 y 100.000): ");
    randomMax = leer_entero();
    while (randomMax < randomMin) {
        printf("El valor maximo del rango no puede ser menor al minimo. Ingrese de vuelta: ");
        randomMax = leer_entero();
    }

    while (!rangoValido(randomMax, randomMin, tamano)) {
        printf("El rango de valores es menor al tamano de la estructura. \n--REINGRESE LOS DATOS NUEVAMENTE POR FAVOR--\n\n");
        printf("Tamano de la cola. ");
        tamano = leer_entero();
        while (tamano > 100000 || tamano <= 0) {
            printf("Tamano invalido. Intentelo de nuevo. ");
            tamano = leer_entero();
        }
        randomMin = 0;
        randomMax = 0;
        printf("[INGRESO - RANGO DE VALORES DEL RANDOM PARA CARGAR COLA]\n");
        printf("Ingrese el valor minimo de los valores random (entre -100.000 y 100.000): ");
        randomMin = leer_entero();
        printf("\n");
        printf("Ingrese el valor maximo de los valores random (entre -100.000 y 100.000): ");
        randomMax = leer_entero();
        while (randomMax < randomMin) {
            printf("El valor maximo del rango no puede ser menor al minimo. Ingrese de vuelta: ");
            randomMax = leer_entero();
        }
    }
    // ---
    int valor = 0;
    for (int i = 0; i < tamano; i++) {
        valor = randomMin + rand() % (randomMax - randomMin + 1);
        while (estaEnLista(listaAux, valor)) {
            valor = randomMin + rand() % (randomMax - randomMin + 1);
        }
        TipoElemento elemento = te_crear(valor);
        l_agregar(listaAux, elemento);
        c_encolar(cola, elemento);
    }
    return cola;
}

// funcion que llena una pila al azar usando rango de randoms
Pila llenar_pila_al_azar() {
    Pila pila = p_crear();
    Lista listaAux = l_crear();
    printf("[INGRESO - PILA]\n");
    printf("Ingrese la longitud de la pila (entre 0 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    int tamano = leer_entero();
    while (tamano < 0 || tamano > 100000) {
        printf("Entrada invalida. Fuera del rango disponible para la pila. Reingrese el tamanio. ");
        tamano = leer_entero();
    }
    if (tamano == 0) {
        printf("PILA VACIA!\n");
        return pila;
    }
    int randomMin = 0;
    int randomMax = 0;
    printf("[INGRESO - RANGO DE VALORES DEL RANDOM PARA CARGAR PILA]\n");
    printf("Ingrese el valor minimo de los valores random (entre -100.000 y 100.000): ");
    randomMin = leer_entero();
    printf("\n");
    printf("Ingrese el valor maximo de los valores random (entre -100.000 y 100.000): ");
    randomMax = leer_entero();
    while (randomMax < randomMin) {
        printf("El valor maximo del rango no puede ser menor al minimo. Ingrese de vuelta: ");
        randomMax = leer_entero();
    }
    // ---
    while (!rangoValido(randomMax, randomMin, tamano)) {
        printf("El rango de valores es menor al tamano de la estructura. \n--REINGRESE LOS DATOS NUEVAMENTE POR FAVOR--\n\n");
        printf("Tamano de la pila. ");
        tamano = leer_entero();
        while (tamano > 100000 || tamano <= 0) {
            printf("Tamano invalido. Intentelo de nuevo. ");
            tamano = leer_entero();
        }
        randomMin = 0;
        randomMax = 0;
        printf("[INGRESO - RANGO DE VALORES DEL RANDOM PARA CARGAR PILA]\n");
        printf("Ingrese el valor minimo de los valores random (entre -100.000 y 100.000): ");
        randomMin = leer_entero();
        printf("\n");
        printf("Ingrese el valor maximo de los valores random (entre -100.000 y 100.000): ");
        randomMax = leer_entero();
        while (randomMax < randomMin) {
            printf("El valor maximo del rango no puede ser menor al minimo. Ingrese de vuelta: ");
            randomMax = leer_entero();
        }
    }

    int valor = 0;
    for (int i = 0; i < tamano; i++) {
        valor = randomMin + rand() % (randomMax - randomMin + 1);
        while (estaEnLista(listaAux, valor)) {
            valor = randomMin + rand() % (randomMax - randomMin + 1);
        }
        TipoElemento elemento = te_crear(valor);
        l_agregar(listaAux, elemento);
        p_apilar(pila, elemento);
    }
    return pila;
}

Pila cargar_pila_manual() {
    Pila pila = p_crear();
    int longitud = 0;
    printf("[INGRESO MANUAL - PILA]\n");
    printf("Ingrese la longitud de la pila (tamano de 0 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la pila, solo se cargaran hasta que se llene la misma.\n");
    longitud = leer_entero();


    while (longitud <= 0 || longitud > 100000) {
        if (longitud == 0){
            break;
        }
        else if (longitud < 1 || longitud > 100000){
            printf("Entrada invalida. Se encuentra fuera del rango disponible para la pila. Reingrese el tamanio. ");
            longitud = leer_entero();
        }
    }
    int i = 1;
    while (i <= longitud){
        if (p_es_llena(pila)){
            printf("La pila ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
            int ingreso = 0;
            printf("Ingrese el elemento %d (entre -100.000 y 100.000).\n", i);
            ingreso = leer_entero();
            TipoElemento elemento = te_crear(ingreso);
            p_apilar(pila, elemento);
            i++;
    }
    return pila;
}

// Función para cargar una cola de forma manual
Cola cargar_cola_manual() {
    Cola cola = c_crear();
    int longitudCola = 0;
    printf("[INGRESO MANUAL - COLA]\n");
    printf("Ingrese la longitud de la cola (entre 0 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la cola, solo se cargaran hasta que se llene la misma.\n");
    longitudCola = leer_entero();
    while ((longitudCola <= 0) || (longitudCola > 100000)){
        if (longitudCola == 0){
            break;
        }
        else if (longitudCola < 1 || longitudCola > 100000){
            printf("Entrada invalida. Se encuentra fuera del rango disponible para la cola. Reingrese el tamanio. ");
            longitudCola = leer_entero();
        }
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

int mostrar_menu() {
    int opcion;
    do {
        printf("Seleccione una opcion:\n");
        printf("1. Carga de datos manual\n");
        printf("2. Carga de datos con valores aleatorios\n");
        printf("Ingrese una opcion (1 o 2): ");
        opcion = leer_entero();
        if (opcion != 1 && opcion != 2) {
            printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 1 && opcion != 2);
    return opcion;
}



// funcion que muestra las posiciones ordinales con la cantidad de veces que se repite
void mostrar_posiciones_ordinales(Lista lista) {
    if (l_es_vacia(lista)) {
        printf("No se repiten posiciones.\n");
    } else {
        Iterador iter = iterador(lista);
        while (hay_siguiente(iter)) {
            TipoElemento elemento = siguiente(iter);
            printf("%d:%s ", elemento->clave, (char*)elemento->valor);
        }
    }
}

// funcion que pide una pila y una cola y retorna una lista con la cantidad de veces que se repiten las claves en ambas
Lista c_ej6_comunesapilaycola(Pila p, Cola c) {
    Lista lista = l_crear();
    Cola copiaCola = copiar_cola(c);
    Pila copiaPila = copiar_pila(p);
    int contadorCola = 0;
    int contadorPila = 0;
    while (!p_es_vacia(copiaPila)) {
        TipoElemento elementoActualPila = p_desapilar(copiaPila);
        contadorPila++;
        while (!c_es_vacia(copiaCola)) {
            TipoElemento elementoActualCola = c_desencolar(copiaCola);
            contadorCola++;
            if (elementoActualCola->clave == elementoActualPila->clave) {
                char posP[10];
                itoa(contadorPila, posP, 10);
                char posC[10];
                itoa(contadorCola, posC, 10);
                char resultado[20] = "";
                strcat(resultado, posP);
                strcat(resultado, ":");
                strcat(resultado, posC);
                char* valorAux = (char*) malloc(sizeof(char) * 10);
                strcpy(valorAux, resultado);
                TipoElemento elementoAgregar = te_crear(elementoActualPila->clave);
                elementoAgregar->valor = valorAux;
                l_agregar(lista, elementoAgregar);
            }
        }
        contadorCola = 0;
        copiaCola = copiar_cola(c);
    }
    return lista;
}

int main() {
    Pila pila;
    Cola cola;
    int opcion = mostrar_menu();

    if (opcion == 1) {
        // Carga manual de datos
        pila = cargar_pila_manual();
        cola = cargar_cola_manual();
    } else if (opcion == 2) {
        // Carga de datos con valores aleatorios
        pila = llenar_pila_al_azar();
        cola = llenar_cola_al_azar();
    }

    printf("------------------\n");
    printf("[PILA]\n");
    p_mostrar(pila);
    printf("[COLA]\n");
    c_mostrar(cola);
    printf("\n[REPETIDOS CON ORDINAL]\n");
    Lista repetidos = c_ej6_comunesapilaycola(pila, cola);
    mostrar_posiciones_ordinales(repetidos);

    return 0;
}
